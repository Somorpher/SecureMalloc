#pragma once

#ifndef _GLIBCXX_STRING
#include <string>
#endif
#ifndef _GLIBCXX_UTILITY
#include <utility>
#endif
#ifndef _STDINT_H
#include <cstdint>
#endif
#ifndef _NEW_
#include <new>
#endif
#ifndef _GLIBCXX_ALGORITHM
#include <algorithm>
#endif
#ifndef _GLIBCXX_IOSTREAM
#include <iostream>
#endif
 
// defining this macro for debugging purposes, remove for production mode.
#define IS_DEBUGGING_CODE 1

#ifndef __MODULE_SAFE_MEMORY_ALLOC__
#define __MODULE_SAFE_MEMORY_ALLOC__

// if macro "IS_DEBUGGING_CODE" is found somewhere in the scope, then optimize = 0
#ifdef IS_DEBUGGING_CODE
#define __with_optimize_perform__ optimize("0")
#else
#define __with_optimize_perform__ optimize("3")
#endif

#if defined(__GNUC__) || defined(__clang__)

#define __hex_parser_attr__ __attribute__((pure, nothrow, always_inline, no_icf, stack_protect, optimize("2"), tainted_args))
#define __attr_inj_idx0__ __attribute__((mode(__pointer__)))
#define __attr_inj_idx1__ __attribute__((mode(__word__)))
#define __attr_inj_idx2__ __attribute__((mode(__pointer__)))
#define __attr_inj_idx3__ __attribute__((nothrow, __with_optimize_perform__))
#define __attr_inj_idx4__ __attribute__((nothrow, __with_optimize_perform__, access(read_write, 1)))
#define __attr_inj_idx5__ __attribute__((nothrow, __with_optimize_perform__))
#define __attr_inj_idx6__ __attribute__((nothrow, __with_optimize_perform__, access(read_write, 1)))
#define __attr_inj_idx7__ __attribute__((nothrow, __with_optimize_perform__, always_inline, leaf, no_sanitize_address, no_sanitize_coverage, no_sanitize_undefined, warn_unused_result))
#define __attr_inj_idx8__ __attribute__((nothrow, __with_optimize_perform__, always_inline, leaf, no_sanitize_address, no_sanitize_coverage, no_sanitize_undefined, warn_unused_result))
#define __attr_inj_idx9__ __attribute__((nothrow, __with_optimize_perform__, leaf, const, always_inline))
#define __attr_inj_idx10__ __attribute__((nothrow, __with_optimize_perform__, leaf, const, always_inline))
#define __attr_inj_idx11__ __attribute__((nothrow, __with_optimize_perform__, leaf, const, always_inline))
#define __attr_inj_idx12__ __attribute__((nothrow, __with_optimize_perform__, always_inline, access(read_only, 1)))
#define __attr_inj_idx13__ __attribute__((nothrow, __with_optimize_perform__, always_inline, access(read_write, 1)))
#define __attr_inj_idx14__ __attribute__((nothrow, __with_optimize_perform__, const, always_inline, leaf, no_sanitize_address, no_sanitize_coverage, no_sanitize_undefined))
#define __attr_inj_idx15__ __attribute__((nothrow, __with_optimize_perform__, always_inline, no_sanitize_address, no_sanitize_coverage, no_sanitize_undefined))
#define __attr_inj_idx0A__ __attribute__((nothrow, __with_optimize_perform__, always_inline))
#define __attr_inj_idx0B__ __attribute__((nothrow, __with_optimize_perform__, always_inline))
#define __attr_inj_idx0C__ __attribute__((__with_optimize_perform__, nothrow, pure, always_inline, no_sanitize_address, no_sanitize_coverage, warn_unused_result))
#define __attr_inj_idx0D__ __attribute__((__with_optimize_perform__, stack_protect, zero_call_used_regs("all"), nothrow, always_inline, no_sanitize_address))
#define __attr_inj_idx0E__ __attribute__((__with_optimize_perform__, stack_protect, zero_call_used_regs("all"), nothrow, always_inline, no_sanitize_address))
#define __attr_inj_idx0F__ __attribute__((__with_optimize_perform__, stack_protect, zero_call_used_regs("all"), nothrow, always_inline, no_sanitize_address))


#else
#define __hex_parser_attr__ [[nothrow]]
#endif

// for converting uintptr_t to hex as string
template <typename T> __hex_parser_attr__ inline static const std::string hexParser(const T _bytes) noexcept
{
    if (sizeof(_bytes) > 0) [[likely]]
    {
        std::stringstream hex_parse;
        hex_parse << "0x" << std::hex << _bytes;
        return hex_parse.str();
    }
    return std::string("0x0");
};

template <typename TX> struct SafeDataAccess
{
    TX data{};
    size_t size{0};
    bool null{true};
};

template <typename T> class SecureMalloc
{

  private:
    bool locked_ = false;
    bool erased_ = false;
    std::string memory_address_;
    std::mutex loc_mtx_;
    #ifdef __attr_inj_idx0__
    __attr_inj_idx0__ T *idx0_data_ = nullptr;
    #else
    T *idx0_data_ = nullptr;
    #endif
    #ifdef __attr_inj_idx1__
    __attr_inj_idx1__ size_t idx1_size_ = 0UL;
    #else
    size_t idx1_size_ = 0UL;
    #endif
    #ifdef __attr_inj_idx2__
    __attr_inj_idx2__ T *data_tmp_ = nullptr;
    #else
    T *data_tmp_ = nullptr;
    #endif

  public:
    /**
     * Default Empty initialization constructor
     */
    __attr_inj_idx3__ SecureMalloc() noexcept
    {
        this->idx0_data_ = new (std::nothrow) T;
        this->data_tmp_ = new (std::nothrow) T;
        std::uintptr_t addr_ptr(reinterpret_cast<std::uintptr_t>(this->idx0_data_));
        this->memory_address_ = hexParser<std::uintptr_t>(addr_ptr);
        this->idx1_size_ = sizeof(T);
    };
    /**
     * T& reference argument initialization constructor
     */
    __attr_inj_idx4__ explicit SecureMalloc(T &_v) noexcept
    {
        this->InitializeBlock(_v);
    };
    /**
     * T* Pointer argument initialization constructor
     */
    __attr_inj_idx5__ explicit SecureMalloc(T *__restrict__ _v) noexcept
    {
        this->InitializeBlock(std::move_if_noexcept(_v));
    };
    /**
     * move semantic const argument initialization constructor
     */
    __attr_inj_idx6__ explicit SecureMalloc(T &&_v) noexcept
    {
        this->InitializeBlock(std::move_if_noexcept(_v));
    };

    SecureMalloc(const SecureMalloc &&other) noexcept : idx0_data_(std::exchange(other.idx0_data_)), idx1_size_(other.idx1_size_), locked_(other.locked_) {};

    // Delete operators
    SecureMalloc(const SecureMalloc &) noexcept = delete;
    SecureMalloc &operator=(const SecureMalloc &) noexcept = delete;
    SecureMalloc &operator=(const SecureMalloc &&) noexcept = delete;

    // Comparision operators
    __attr_inj_idx7__ inline const bool operator==(
        const SecureMalloc &other) const noexcept
    {
        return this->memory_address_.compare(other.address_) == 0;
    };
    __attr_inj_idx8__ inline const bool operator!=(
        const SecureMalloc &other) const noexcept
    {
        return this->memory_address_.compare(other.address_) != 0;
    };

    /**
     * get idx0_data_ section.
     * @param void
     * @return SafeDataAccess<T> read-only access to private data member pointer
     */
    __attr_inj_idx9__ inline const SafeDataAccess<T> getData(void) noexcept
    {
        struct SafeDataAccess<T> _rv;
        if (this->idx0_data_ == nullptr || this->locked_)
        {
            return _rv;
        }
        _rv.data = *this->idx0_data_;
        _rv.null = false;
        _rv.size = sizeof(*this->idx0_data_);
        return _rv;
    };

    /**
     * get idx0_data_ section.
     * @param void
     * @return T* read-write access to private data member pointer
     */
    __attr_inj_idx10__ inline T *getRawPtr(void) noexcept
    {
        return this->locked_ ? this->data_tmp_ : this->idx0_data_;
    };

    /**
     * get memory address section.
     * @param void
     * @return std::intptr_t read-only access to private data member pointer address_
     */
    __attr_inj_idx11__ inline const std::string getAddress(void) noexcept
    {
        return std::as_const(this->memory_address_);
    };

    /**
     * set idx0_data_ section.
     * @param T& new data
     */
    __attr_inj_idx12__ inline void Allocate(T &_d) noexcept
    {
        this->loc_mtx_.lock();
        if (this->locked_)
        {
            this->loc_mtx_.unlock();
            return;
        }
        *this->idx0_data_ = std::move(_d);
        this->loc_mtx_.unlock();
    };
    /**
     * set idx0_data_ section.
     * @param T new data
     */
    __attr_inj_idx13__ inline void Allocate(const T _d) noexcept
    {
        this->loc_mtx_.lock();
        if (this->locked_)
        {
            this->loc_mtx_.unlock();
            return;
        }
        *this->idx0_data_ = std::move(_d);
        this->loc_mtx_.unlock();
    };

    /**
     * Check if idx0_data_ section is locked_!
     */
    __attr_inj_idx14__ inline const bool isLocked(void) const noexcept
    {
        return this->locked_;
    };

    /**
     * Lock Access to idx0_data_ section.
     */
    __attr_inj_idx15__ inline void Lock(void) noexcept
    {
        this->loc_mtx_.lock();
        this->locked_ = true;
        this->loc_mtx_.unlock();
    };

    /**
     * Unlock access to idx0_data_ section
     */
    __attr_inj_idx0A__ inline void Unlock(void) noexcept
    {
        this->loc_mtx_.lock();
        this->locked_ = false;
        this->loc_mtx_.unlock();
    };

    /**
     * Wipe Data slots
     */
    __attr_inj_idx0B__ inline void Deallocate() noexcept
    {
        this->loc_mtx_.lock();
        if (this->erased_ == false)
        {
            this->erased_ = true;
            if (this->idx0_data_ != nullptr)
                delete this->idx0_data_; // calls the destructor of idx0_data_ object

            if (this->data_tmp_ != nullptr)
                delete this->data_tmp_;
        }
        this->loc_mtx_.unlock();
    };

    /**
     * Check if points to null value address.
     * @returns true if null, false otherwise.
     *
     */
    __attr_inj_idx0C__ inline const bool PtrNullValue(void) noexcept
    {
        return this->idx0_data_ == nullptr;
    };

    ~SecureMalloc() noexcept
    {
        if (!this->erased_)
            this->Deallocate();
    };

  private:

   /**
   * Deals with l-value data/object
   * @param T& l-value reference to _v(data to allocate)
   * @returns void
  */
    __attr_inj_idx0D__ inline void InitializeBlock(T &_v) noexcept
    {
        if (sizeof(_v) > 0)
        {
            this->idx0_data_ = new (std::nothrow) T(_v);
            this->data_tmp_ = new (std::nothrow) T;
            std::uintptr_t addr_ptr = reinterpret_cast<std::uintptr_t>(this->idx0_data_);
            this->memory_address_ = hexParser<std::uintptr_t>(addr_ptr);
            this->idx1_size_ = sizeof(_v);
        }
    };
      /**
   * Deals with l-value/r-value object/data
   * @param T* restricted l-value/r-value pointer address to _v(data to allocate)
   * @returns void
  */
    __attr_inj_idx0E__ inline void InitializeBlock(T *__restrict__ _v) noexcept
    {
        if (sizeof(*_v) > 0 && _v != nullptr)
        {
            this->idx0_data_ = std::move_if_noexcept(_v);
            this->data_tmp_ = new (std::nothrow) T;
            std::uintptr_t addr_ptr = reinterpret_cast<std::uintptr_t>(this->idx0_data_);
            this->memory_address_ = hexParser<std::uintptr_t>(addr_ptr);
            this->idx1_size_ = sizeof(*_v);
        }
    };
     /**
   * Deals with r-value data/object, l-value will not work as object needs to be moved with std::move.
   * @param T&& r-value reference to _v(data to allocate)
   * @returns void
  */
    __attr_inj_idx0F__ inline void InitializeBlock(T &&_v) noexcept
    {
        if (sizeof(_v) > 0)
        {
            this->idx0_data_ = new (std::nothrow) T(std::move_if_noexcept(_v));
            this->data_tmp_ = this->idx0_data_ != nullptr ? new (std::nothrow) T(*this->idx0_data_) : new (std::nothrow) T;
            std::uintptr_t addr_ptr = reinterpret_cast<std::uintptr_t>(this->idx0_data_);
            this->memory_address_ = hexParser<std::uintptr_t>(addr_ptr);
            this->idx1_size_ = sizeof(_v);
        }
    };
};

#endif
