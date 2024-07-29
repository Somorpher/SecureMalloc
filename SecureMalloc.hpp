#pragma once

#ifndef __UNIT_LIBS_INTERSECTION__
#include "../config/include.hpp"
#endif

#ifndef __UNIT_TYPES__
#include "types.hpp"
#endif

#ifndef __UNIT_SHARED_FUNCTIONS__
#include "shared.hpp"
#endif

#ifndef __UNIT_SAFE_MEMORY_ALLOC__
#define __UNIT_SAFE_MEMORY_ALLOC__

// if macro "IS_DEBUGGING_CODE" is found somewhere, then optimize = 0
#ifdef IS_DEBUGGING_CODE
#define __with_optimize_perform__ optimize("0")
#else
#define __with_optimize_perform__ optimize("3")
#endif


template <typename T> class SecureMalloc
{

  private:
    bool locked = false;
    bool erased = false;
    Types::String_t memory_address;

    public: __attribute__((mode(__pointer__))) T *data_ = nullptr;
    private: __attribute__((mode(__word__))) size_t size_ = 0UL;
    __attribute__((mode(__pointer__))) T *data_tmp = nullptr;

  public:
    __attribute__((nothrow, __with_optimize_perform__)) SecureMalloc() noexcept
    {
        this->data_ = new (std::nothrow) T;
        this->data_tmp = new(std::nothrow) T(*this->data_);
        std::uintptr_t addr_ptr = reinterpret_cast<std::uintptr_t>(this->data_);
        this->memory_address = hexParse<std::uintptr_t>(addr_ptr);
        this->size_ = sizeof(T);
    };

    __attribute__((nothrow, __with_optimize_perform__, access(read_only, 1))) explicit SecureMalloc(const T &_v) noexcept
    {
        if (sizeof(_v) > 0)
        {
            this->data_ = new (std::nothrow) T(std::exchange(_v));
            this->data_tmp = new(std::nothrow) T(*this->data_);
            std::uintptr_t addr_ptr = reinterpret_cast<std::uintptr_t>(this->data_);
            this->memory_address = hexParse<std::uintptr_t>(addr_ptr);
            this->size_ = sizeof(_v);
        }
    };

    __attribute__((nothrow, __with_optimize_perform__, access(read_only, 1))) explicit SecureMalloc(const T &&_v) noexcept
    {
        if (sizeof(_v) > 0)
        {
            this->data_ = new (std::nothrow) T(std::move(_v));
            this->data_tmp = new(std::nothrow) T(*this->data_);
            std::uintptr_t addr_ptr = reinterpret_cast<std::uintptr_t>(this->data_);
            this->memory_address = hexParse<std::uintptr_t>(addr_ptr);
            this->size_ = sizeof(_v);
        }
    };

    /**
     * get data_ section.
     * @param void
     * @return T* read-write access to private data member pointer
     */
    __attribute__((nothrow, __with_optimize_perform__, leaf, const, always_inline)) inline T *getData(void) noexcept
    {
        return this->locked ? nullptr : this->data_;
    };

    /**
     * get memory address data section.
     * @param void
     * @return std::intptr_t read-only access to private data member pointer address_
     */
    __attribute__((nothrow, __with_optimize_perform__, leaf, const, always_inline)) inline const Types::String_t getAddress(void) noexcept
    {
        return std::as_const(this->memory_address);
    };

    /**
     * set data_ section.
     * @param T& new data
     */
    __attribute__((nothrow, __with_optimize_perform__, always_inline)) inline void Allocate(T &_d) noexcept
    {
        if (this->locked)
            return;
        *this->data_ = std::move(_d);
    };

    /**
     * Check if data_ section is locked!
     */
    __attribute__((nothrow, __with_optimize_perform__, const, always_inline, leaf, no_sanitize_address, no_sanitize_coverage, no_sanitize_undefined)) inline const bool isLocked(void) const noexcept
    {
        return this->locked;
    };

    /**
     * Lock Access to data_ section.
     */
    __attribute__((nothrow, __with_optimize_perform__, always_inline, no_sanitize_address, no_sanitize_coverage, no_sanitize_undefined)) inline void Lock(void) noexcept
    {
        this->locked = true;
        *this->data_tmp = *this->data_;
        delete this->data_;
        this->data_ = nullptr;
    };

    /**
     * Unlock access to data_ section
     */
    __attribute__((nothrow, __with_optimize_perform__, always_inline, no_sanitize_address, no_sanitize_coverage, no_sanitize_undefined)) inline void Unlock(void) noexcept
    {
        this->locked = false;
        *this->data_ = *this->data_tmp;
        delete this->data_tmp;
        this->data_tmp = nullptr;
    };

    SecureMalloc(const SecureMalloc &) noexcept = delete;
    SecureMalloc(const SecureMalloc &&other) noexcept : data_(std::exchange(other.data_)), size_(other.size_), locked(other.locked) {};
    SecureMalloc &operator=(const SecureMalloc &) noexcept = delete;
    SecureMalloc &operator=(const SecureMalloc &&) noexcept = delete;
    __attribute__((nothrow, __with_optimize_perform__, always_inline, leaf, no_sanitize_address, no_sanitize_coverage, no_sanitize_undefined, warn_unused_result)) inline const bool &operator==(
        const SecureMalloc &other) const noexcept
    {
        return this->memory_address.compare(other.address_) == 0; 
    };

    /**
     * Clean Data.
     */
    __attribute__((nothrow, __with_optimize_perform__, always_inline, no_sanitize_address, no_sanitize_coverage, no_sanitize_undefined)) inline void Deallocate() noexcept
    {
        if (!this->erased)
        {
            this->erased = true;
            if (this->data_ != nullptr)
                delete this->data_; // calls the destructor of data_ object

            if (this->data_tmp != nullptr)
                delete this->data_tmp;
        }
    }

    ~SecureMalloc() noexcept
    {
        this->Deallocate();
    };
};

#endif
