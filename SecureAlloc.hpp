#pragma once

#ifndef __MODULE_SAFE_MEMORY_ALLOC__
#define __MODULE_SAFE_MEMORY_ALLOC__ 1

#include <cstdint>     // for std::uintptr_t
#include <iostream>    // for std::cout and std::endl
#include <mutex>       // for std::mutex and std::lock_guard
#include <sstream>     // for std::stringstream
#include <stdexcept>   // for std::stoll
#include <type_traits> // for std::is_array_v, std::is_pointer_v, std::enable_if, and std::is_reference_v
#include <stdlib.h>
#include <new>

#if defined(__GNUC__) || defined(__clang__)

#define __a_inj_dc __attribute__((nothrow, leaf, optimize("3"), section(".text"))) // attribute injection for dc(default constructor)
#define __a_inj_cctor __attribute__((nothrow, leaf, optimize("3"), access(read_only, 1))) // attribute injection for copy constructor
#define __a_inj_mctor __attribute__((nothrow, leaf, optimize("3"), access(read_write, 1))) // attribute injection for move constructor
#define __a_inj_eqop __attribute__((nothrow, leaf, optimize("3"), access(read_only, 1))) // attribute injection for equality operator
#define __a_inj_uneqop __attribute__((nothrow, leaf, optimize("3"), access(read_only, 1))) // attribute injection for unequality operator
#define __a_inj_get __attribute__((nothrow, leaf, optimize("0"), pure, always_inline, no_sanitize_address, no_sanitize_undefined, warn_unused_result)) // attribute injection for get method
#define __a_inj_alloc __attribute__((nothrow, leaf, optimize("3"), access(read_only, 1), always_inline, no_sanitize_address, no_sanitize_undefined)) // attribute injection for alloc method
#define __a_inj_free __attribute__((nothrow, leaf, optimize("3"), always_inline, stack_protect, no_sanitize_address, no_sanitize_undefined)) // attribute injection for free method
#define __a_inj_hex_p __attribute__((nothrow, optimize("3"), always_inline, stack_protect, no_sanitize_address, no_sanitize_undefined, warn_unused_result, access(read_only, 1))) // attribute injection for free method

#else

#define __a_inj_dc [[nothrow]]
#define __a_inj_cctor [[nodiscard, nothrow]]
#define __a_inj_mctor [[nodiscard, nothrow]]
#define __a_inj_eqop [[nodiscard, nothrow]]
#define __a_inj_uneqop [[nodiscard, nothrow]]
#define __a_inj_get [[nodiscard, nothrow]]
#define __a_inj_alloc [[nothrow]]
#define __a_inj_free [[nothrow]]
#define __a_inj_hex_p [[nodiscard, nothrow]]
#endif


template <typename _cT, typename = std::enable_if<!std::is_reference_v<_cT> &&!std::is_pointer_v<_cT>>> class SecureAlloc
{
    _cT *_data_;
    size_t _block_size_;
    std::uintptr_t _address_;
    bool _is_free_ = true;
    bool _is_init_ = false;
    std::mutex _Mtx_; // for thread safe access, race conditions, dead-locks, etc...
  public:
    __a_inj_dc explicit SecureAlloc() noexcept
    {
        static_assert(!std::is_array_v<_cT> &&!std::is_pointer_v<_cT>, "no Array allocatable or Pointer...");
        this->_data_ = new (std::nothrow) _cT;
        this->_address_ = this->__HexAddress(reinterpret_cast<std::uintptr_t>(this->_data_));
        this->_block_size_ = sizeof(*this->_data_);
        this->_is_init_ = true;
        this->_is_free_ = false;
    };

    __a_inj_cctor explicit SecureAlloc(const _cT _Pv) noexcept
    {
        static_assert(!std::is_array_v<_cT> &&!std::is_pointer_v<_cT>, "no Array or Pointer allocatable...");
        this->_data_ = new (std::nothrow) _cT(std::move(_Pv));
        this->_address_ = this->__HexAddress(reinterpret_cast<std::uintptr_t>(this->_data_));
        this->_block_size_ = sizeof(*this->_data_);
        this->_is_init_ = true;
        this->_is_free_ = false;
    };

    // ------ COPY CONSTRUCTOR/+OPERATOR ------
    __a_inj_cctor explicit SecureAlloc(const SecureAlloc &_o) noexcept : _block_size_(_o._block_size_), _Mtx_(_o._Mtx_), _is_free_(_o._is_free_), _is_init_(_o._is_init_)
    {
        *this->_data_ = std::move(*_o._data_);
    };
    __a_inj_eqop SecureAlloc &operator=(const SecureAlloc &_o) noexcept
    {
        if (*this!= _o)
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
    __a_inj_mctor explicit SecureAlloc(SecureAlloc &&_o) noexcept : _data_(std::move_if_noexcept(_o._data_)), _block_size_(_o._block_size_), _Mtx_(std::move(_o._Mtx_)), _is_free_(_o._is_free_), _is_init_(_o._is_init_)
    {
        _o.~SecureAlloc();
    };
    __a_inj_eqop SecureAlloc &operator=(SecureAlloc &&_o) noexcept
    {
        if (this!= _o)
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
    __a_inj_eqop constexpr inline bool operator==(const SecureAlloc &_o) noexcept
    {
        return this->_address_ == _o._address_;
    };

    __a_inj_uneqop constexpr inline bool operator!=(const SecureAlloc &_o) noexcept
    {
        return!(this->_address_ == _o._address_);
    };

    /**
     * Get allocated block.
     * @returns _cT*
     */
    __a_inj_get constexpr _cT *Get(void) noexcept
    {
        return this->_is_free_ ||!this->_is_init_? nullptr : this->_data_;
    };

    /**
     * Get allocated block size.
     * @returns const size_t&
     */
    __a_inj_get constexpr size_t &GetSize(void) noexcept
    {
        return this->_block_size_;
    };

    /**
     * Get Allocation address.
     * @returns const std::uintptr_t&
     */
    __a_inj_get constexpr std::uintptr_t &GetAddress(void) noexcept
    {
        return this->_address_;
    };

    /**
     * Allocate data.
     * @param const _cT data to allocate.
     */
    __a_inj_alloc constexpr void Alloc(const _cT _mv) noexcept
    {
        std::lock_guard<std::mutex> _l(this->_Mtx_);
        static_assert(!std::is_array_v<_cT> &&!std::is_pointer_v<_cT>, "no Array or Pointer can be set!");
        if (this->_is_free_ ||!this->_is_init_) [[unlikely]]
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
    __a_inj_get constexpr bool IsNullPtr(void) noexcept
    {
        return this->_is_free_ ||!this->_is_init_ || this->_data_ == nullptr;
    };

    /**
     * Free allocated data
     */
    __a_inj_free inline void Free(void) noexcept
    {
        std::lock_guard<std::mutex> _l(this->_Mtx_);
        if (!this->_is_free_ && this->_is_init_) [[likely]]
        {
            this->_is_free_ = true;
            this->_is_init_ = false;
            delete this->_data_;
        }
    };

    ~SecureAlloc() noexcept
    {
        std::cout << "SecureAlloc Destructor...\n";
        this->Free();
    };

  private:
    /**
     * convert dec to hex.
     * @param const std::uintptr_t&
     * @returns const std::uintptr_t
     */
    __a_inj_hex_p const std::uintptr_t __HexAddress(const std::uintptr_t &_addr) noexcept
    {
        size_t hex_value;
        std::stringstream _p;
        _p << std::hex << _addr;
        hex_value = std::stoll(_p.str(), NULL, 16);
        std::cout.setstate(std::ios_base::failbit);
        std::cout << "GOOD: " << std::hex << hex_value << "\n";
        std::cout.clear();
        return hex_value;
    };
};

#endif
