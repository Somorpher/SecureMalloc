/**
 *                         Reference Page
 * --------------------------------------------------------------
 *                                                               |
 * Url             = https://github.com/Somorpher/SecureMalloc   |
 *                                                               |
 * Written by      = Somorpher                                   |
 *                                                               |
 * DateTime        = Tue Jul 30 17:38:52 UTC 2024                |
 *                                                               |
 * --------------------------------------------------------------
 *
 *
 *
 * The SecureMalloc class is a C++ class designed to manage memory allocation and deallocation
 * for a given type T. The class provides a secure way to allocate and deallocate memory,
 * ensuring thread safety and preventing common memory-related issues such as memory leaks
 * and double-free errors.
 *
 * ----------------
 * Class Structure |
 * ----------------
 *
 * The SecureMalloc class is defined as a template class, taking a single type parameter T.
 * The class has a private member variable idx0_data_ of type T, which represents the
 * allocated memory block. Additionally, the class has a private member variable data_tmp_
 * of type T, which serves as a temporary storage for the allocated memory block.
 * The class also has several private member functions, including InitializeBlock,
 * Allocate, Lock, Unlock, and Deallocate. These functions are responsible for initializing
 * the allocated memory block, allocating and deallocating memory, locking and unlocking access
 * to the memory block, and deallocating the memory block, respectively.
 *
 * ------------------
 * Memory Management |
 * ------------------
 *
 * The SecureMalloc class uses a custom memory management scheme, which involves allocating
 * memory using the new operator and storing the allocated memory block in the idx0_data_
 * member variable. The class also uses a temporary storage data_tmp_ to store the allocated
 * memory block, which is used to prevent memory leaks in case of exceptions. provides
 * several methods for allocating and deallocating memory, including Allocate and Deallocate.
 * The Allocate method allocates a new memory block of size T and stores it in the idx0_data_
 * member variable. The Deallocate method deallocates the allocated memory block and sets the
 * idx0_data_ member variable to nullptr.
 *
 * --------------
 * Thread Safety |
 * --------------
 *
 * The SecureMalloc class is designed to be thread-safe, using a mutex (loc_mtx_) to synchronize
 * access to the allocated memory block. The Lock and Unlock methods are used to acquire and
 * release the mutex, respectively, ensuring that only one thread can access the allocated memory
 * block at a time.
 *
 * -------------------------
 * Attributes and Notations |
 * -------------------------
 *
 * The SecureMalloc class uses several attributes and notations, including __attr_inj_idxX__
 * and __with_optimize_perform__. These attributes and notations are used to optimize the
 * performance of the class and ensure that the allocated memory block is properly aligned and padded.
 *
 * -----------------------------
 * Constructors and Destructors |
 * -----------------------------
 *
 * The SecureMalloc class has several constructors, including a default constructor,
 * a copy constructor, and a move constructor.
 *
 */
#pragma once

namespace SecureMallocModule
{
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

#define __attr_inj_idx3__ [[nothrow]]
#define __attr_inj_idx4__ [[nothrow]]
#define __attr_inj_idx5__ [[nothrow]]
#define __attr_inj_idx6__ [[nothrow]]
#define __attr_inj_idx7__ [[nothrow]]
#define __attr_inj_idx8__ [[nothrow]]
#define __attr_inj_idx9__ [[nothrow]]
#define __attr_inj_idx10__ [[nothrow]]
#define __attr_inj_idx11__ [[nothrow]]
#define __attr_inj_idx12__ [[nothrow]]
#define __attr_inj_idx13__ [[nothrow]]
#define __attr_inj_idx14__ [[nothrow]]
#define __attr_inj_idx15__ [[nothrow]]
#define __attr_inj_idx0A__ [[nothrow]]
#define __attr_inj_idx0B__ [[nothrow]]
#define __attr_inj_idx0C__ [[nothrow]]
#define __attr_inj_idx0D__ [[nothrow]]
#define __attr_inj_idx0E__ [[nothrow]]
#define __attr_inj_idx0F__ [[nothrow]]
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
    __attr_inj_idx3__ SecureMalloc() noexcept
    {
        this->idx0_data_ = new (std::nothrow) T;
        this->data_tmp_ = new (std::nothrow) T;
        std::uintptr_t addr_ptr(reinterpret_cast<std::uintptr_t>(this->idx0_data_));
        this->memory_address_ = hexParser<std::uintptr_t>(addr_ptr);
        this->idx1_size_ = sizeof(T);
    };

    __attr_inj_idx4__ explicit SecureMalloc(T &_v) noexcept
    {
        this->InitializeBlock(_v);
    };

    __attr_inj_idx5__ explicit SecureMalloc(T *__restrict__ _v) noexcept
    {
        this->InitializeBlock(std::move_if_noexcept(_v));
    };

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
    __attr_inj_idx7__ inline const bool operator==(const SecureMalloc &other) const noexcept
    {
        return this->memory_address_.compare(other.address_) == 0;
    };
    __attr_inj_idx8__ inline const bool operator!=(const SecureMalloc &other) const noexcept
    {
        return this->memory_address_.compare(other.address_) != 0;
    };

    /**
     * get idx0_data_ data block.
     * @param void
     * @return SafeDataAccess<T> read-only
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
     * get idx0_data_ raw block.
     * @param void
     * @return T* read-write
     */
    __attr_inj_idx10__ inline T *getRawPtr(void) noexcept
    {
        return this->locked_ ? this->data_tmp_ : this->idx0_data_;
    };

    /**
     * get memory address.
     * @param void
     * @return std::intptr_t read-only
     */
    __attr_inj_idx11__ inline const std::string getAddress(void) noexcept
    {
        return std::as_const(this->memory_address_);
    };

    /**
     * set idx0_data_ block value.
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
     * set idx0_data_ block value.
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
     * Check if idx0_data_ locked!
     */
    __attr_inj_idx14__ inline const bool isLocked(void) const noexcept
    {
        return this->locked_;
    };

    /**
     * Lock idx0_data_ access.
     */
    __attr_inj_idx15__ inline void Lock(void) noexcept
    {
        this->loc_mtx_.lock();
        this->locked_ = true;
        this->loc_mtx_.unlock();
    };

    /**
     * Unlock idx0_data_ access
     */
    __attr_inj_idx0A__ inline void Unlock(void) noexcept
    {
        this->loc_mtx_.lock();
        this->locked_ = false;
        this->loc_mtx_.unlock();
    };

    /**
     * Wipe Data
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
     * l-value reference block initialization
     * @param T&
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
     * l-value reference block initialization
     * @param T*
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
     * r-value/l-value reference block initialization
     * @param T&&
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

}; // namespace SecureMallocModule
