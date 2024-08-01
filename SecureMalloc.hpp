template <typename _cT, typename = std::enable_if<!std::is_reference_v<_cT> && !std::is_pointer_v<_cT>>> class Malloc
{
    _cT *_data_;
    size_t _block_size_;
    std::uintptr_t _address_;
    bool _is_free_ = true;
    bool _is_init_ = false;
    std::mutex _Mtx_; // for thread safe access, race conditions, dead-locks, etc...
  public:
    __attribute__((nothrow, leaf, optimize("3"), section(".text"))) explicit Malloc() noexcept
    {
        static_assert(!std::is_array_v<_cT> && !std::is_pointer_v<_cT>, "no Array allocatable or Pointer...");
        this->_data_ = new (std::nothrow) _cT;
        this->_address_ = this->__HexAddress(reinterpret_cast<std::uintptr_t>(this->_data_));
        this->_block_size_ = sizeof(*this->_data_);
        this->_is_init_ = true;
        this->_is_free_ = false;
    };

    __attribute__((nothrow, leaf, optimize("3"), access(read_only, 1))) explicit Malloc(const _cT _Pv) noexcept
    {
        static_assert(!std::is_array_v<_cT> && !std::is_pointer_v<_cT>, "no Array or Pointer allocatable...");
        this->_data_ = new (std::nothrow) _cT(std::move(_Pv));
        this->_address_ = this->__HexAddress(reinterpret_cast<std::uintptr_t>(this->_data_));
        this->_block_size_ = sizeof(*this->_data_);
        this->_is_init_ = true;
        this->_is_free_ = false;
    };

    // ------ COPY CONSTRUCTOR/+OPERATOR ------
    __attribute__((nothrow, leaf, optimize("3"), access(read_only, 1))) explicit Malloc(const Malloc &_o) noexcept : _block_size_(_o._block_size_), _Mtx_(_o._Mtx_), _is_free_(_o._is_free_), _is_init_(_o._is_init_)
    {
        *this->_data_ = std::move(*_o._data_);
    };
    __attribute__((nothrow, leaf, optimize("3"), access(read_only, 1))) Malloc &operator=(const Malloc &_o) noexcept
    {
        if (*this != _o)
        {
            this->_data_ = std::move(*(_o._data_));
            this->_block_size_ = _o._block_size_;
            this->_Mtx_ = std::move(_o._Mtx_);
            this->_is_free_ = _o._is_free_;
            this->_is_init_ = _o._is_init_;
        }
        return *this;
    };

    // ------ MOVE CONSTRUCTOR/+OPERATOR ------
    __attribute__((nothrow, leaf, optimize("3"), access(read_write, 1))) explicit Malloc(Malloc &&_o) noexcept : _data_(std::move_if_noexcept(_o._data_)), _block_size_(_o._block_size_), _Mtx_(std::move(_o._Mtx_)), _is_free_(_o._is_free_), _is_init_(_o._is_init_)
    {
        _o.~Malloc();
    };
    __attribute__((nothrow, leaf, optimize("3"), access(read_write, 1))) Malloc &operator=(Malloc &&_o) noexcept
    {
        if (this != _o)
        {
            this->_data_ = std::move_if_noexcept<_cT>(_o._data_);
            this->_block_size_ = _o._block_size_;
            this->_Mtx_ = std::move(_o._Mtx_);
            this->_is_free_ = _o._is_free_;
            this->_is_init_ = _o._is_init_;
            _o.Free();
        }
        return *this;
    };

    // Equality Comparision Operators
    constexpr inline bool operator==(const Malloc &_o) noexcept
    {
        return this->_address_ == _o._address_;
    };

    constexpr inline bool operator!=(const Malloc &_o) noexcept
    {
        return !(this->_address_ == _o._address_);
    };

    /**
     * Get allocated block.
     * @returns _cT*
    */
    __attribute__((nothrow, leaf, optimize("0"), pure, always_inline, no_sanitize_address, no_sanitize_undefined, warn_unused_result)) constexpr _cT *Get(void) noexcept
    {
        return this->_is_free_ || !this->_is_init_ ? nullptr : this->_data_;
    };

    /**
     * Get allocated block size.
     * @returns const size_t&
    */
    __attribute__((nothrow, leaf, optimize("0"), pure, always_inline, no_sanitize_address, no_sanitize_undefined, warn_unused_result)) constexpr size_t &GetSize(void) noexcept
    {
        return this->_block_size_;
    };

    /**
     * Get Allocation address.
     * @returns const std::uintptr_t&
    */
    __attribute__((nothrow, leaf, optimize("0"), pure, always_inline, no_sanitize_address, no_sanitize_undefined, warn_unused_result)) constexpr std::uintptr_t &GetAddress(void) noexcept
    {
        return this->_address_;
    };

    /**
     * Allocate data.
     * @param const _cT data to allocate.
    */
    __attribute__((nothrow, leaf, optimize("3"), access(read_only, 1), always_inline, no_sanitize_address, no_sanitize_undefined)) constexpr void Alloc(const _cT _mv) noexcept
    {
        std::lock_guard<std::mutex> _l(this->_Mtx_);
        static_assert(!std::is_array_v<_cT> && !std::is_pointer_v<_cT>, "no Array or Pointer can be set!");
        if (this->_is_free_ || !this->_is_init_) [[unlikely]]
            this->_data_ = new (std::nothrow) _cT(std::move(_mv));
        else
            *this->_data_ = std::move(_mv);
        this->_is_free_ = false;
        this->_is_init_ = true;
    };

    /**
     * check is allocation is null.
     * @returns bool
    */
    __attribute__((nothrow, leaf, optimize("0"), pure, always_inline, no_sanitize_address, no_sanitize_undefined, warn_unused_result)) constexpr bool IsNullPtr(void) noexcept
    {
        return this->_is_free_ || !this->_is_init_ || this->_data_ == nullptr;
    };

    /**
     * Free allocated data
    */
    __attribute__((nothrow, leaf, optimize("3"), always_inline, stack_protect, no_sanitize_address, no_sanitize_undefined)) inline void Free(void) noexcept
    {
        std::lock_guard<std::mutex> _l(this->_Mtx_);
        if (!this->_is_free_ && this->_is_init_) [[likely]]
        {
            this->_is_free_ = true;
            this->_is_init_ = false;
            delete this->_data_;
        }
    };

    ~Malloc() noexcept
    {
        std::cout << "Malloc Destructor...\n";
        this->Free();
    };

  private:

  /**
   * convert dec to hex.
   * @param const std::uintptr_t&
   * @returns const std::uintptr_t
  */
    const std::uintptr_t __HexAddress(const std::uintptr_t &_addr) noexcept
    {
    size_t hex_value;
    std::stringstream _p;
    _p << std::hex << _addr;
    hex_value = std::stoll(_p.str(), NULL, 16);
    std::cout.setstate(std::ios_base::failbit);
    std::cout <<"GOOD: " << std::hex << hex_value <<"\n";
    std::cout.clear();
    return hex_value;
    };
};
