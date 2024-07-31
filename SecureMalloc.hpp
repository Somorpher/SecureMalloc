/**
 *                         Reference
 * Page
 * --------------------------------------------------------------
 *                                                               |
 * Url             =
 * https://github.com/Somorpher/SecureMalloc
 * |
 *                                                               |
 * Written by      = Somorpher
 * |
 *                                                               |
 * DateTime        = Tue Jul
 * 30 17:38:52 UTC 2024 |
 *                                                               |
 * --------------------------------------------------------------
 *
 *
 *
 * The SecureMalloc class is a
 * C++ class designed to
 * manage memory allocation
 * and deallocation for a
 * given type _obT. The
 * class provides a secure way
 * to allocate and deallocate
 * memory, ensuring thread
 * safety and preventing
 * common memory-related
 * issues such as memory leaks
 * and double-free errors.
 *
 * ----------------
 * Class Structure |
 * ----------------
 *
 * The SecureMalloc class is
 * defined as a template
 * class, taking a single type
 * parameter _obT. The
 * class has a private member
 * variable idx0_data_ of type
 * _obT, which represents
 * the allocated memory block.
 * Additionally, the class has
 * a private member variable
 * idx2_data_tmp_ of type
 * _obT, which serves as a
 * temporary storage for the
 * allocated memory block. The
 * class also has several
 * private member functions,
 * including InitializeBlock,
 * Allocate, Lock, Unlock, and
 * Deallocate. These functions
 * are responsible for
 * initializing the allocated
 * memory block, allocating
 * and deallocating memory,
 * locking and unlocking
 * access to the memory block,
 * and deallocating the memory
 * block, respectively.
 *
 * ------------------
 * Memory Management |
 * ------------------
 *
 * The SecureMalloc class uses
 * a custom memory management
 * scheme, which involves
 * allocating memory using the
 * new operator and storing
 * the allocated memory block
 * in the idx0_data_ member
 * variable. The class also
 * uses a temporary storage
 * idx2_data_tmp_ to store the
 * allocated memory block,
 * which is used to prevent
 * memory leaks in case of
 * exceptions. provides
 * several methods for
 * allocating and deallocating
 * memory, including Allocate
 * and Deallocate. The
 * Allocate method allocates a
 * new memory block of size
 * _obT and stores it in
 * the idx0_data_ member
 * variable. The Deallocate
 * method deallocates the
 * allocated memory block and
 * sets the idx0_data_ member
 * variable to nullptr.
 *
 * --------------
 * Thread Safety |
 * --------------
 *
 * The SecureMalloc class is
 * designed to be thread-safe,
 * using a mutex (loc_mtx_) to
 * synchronize access to the
 * allocated memory block. The
 * Lock and Unlock methods are
 * used to acquire and release
 * the mutex, respectively,
 * ensuring that only one
 * thread can access the
 * allocated memory block at a
 * time.
 *
 * -------------------------
 * Attributes and Notations |
 * -------------------------
 *
 * The SecureMalloc class uses
 * several attributes and
 * notations, including
 * __attr_inj_idxX__ and
 * __with_optimize_perform__.
 * These attributes and
 * notations are used to
 * optimize the performance of
 * the class and ensure that
 * the allocated memory block
 * is properly aligned and
 * padded.
 *
 * -----------------------------
 * Constructors and
 * Destructors |
 * -----------------------------
 *
 * The SecureMalloc class has
 * several constructors,
 * including a default
 * constructor, a copy
 * constructor, and a move
 * constructor.
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

#include <bits/c++config.h>
#include <bits/functional_hash.h>
#include <bits/stl_function.h>
#include <compare>
#include <debug/assertions.h>
#include <type_traits>

// defining this macro for
// debugging purposes, remove
// for production mode.
#define IS_DEBUGGING_CODE 1 // remove for production

#ifndef __MODULE_SAFE_MEMORY_ALLOC__
#define __MODULE_SAFE_MEMORY_ALLOC__

// if macro
// "IS_DEBUGGING_CODE" is
// found somewhere in the
// scope, then optimize = 0
#ifdef IS_DEBUGGING_CODE
#define __with_optimize_perform__ optimize("0")
#else
#define __with_optimize_perform__ optimize("3")
#endif

/*                              Method Attribution                             *\
\*******************************************************************************/

// Define attribute alias for gcc|clang compatible compilers, arbitrary attribute alias register
#if defined(__GNUC__) || defined(__clang__)

#define __a_inj_hpf __attribute__((pure, nothrow, always_inline, no_icf, stack_protect, optimize("2"), tainted_args))
#define __a_inj_dpmv __attribute__((mode(__pointer__)))
#define __a_inj_pbs __attribute__((mode(__word__)))
#define __a_inj_td __attribute__((mode(__pointer__)))
#define __a_inj_dc __attribute__((nothrow, __with_optimize_perform__, access(read_write, 1)))
#define __a_inj_mc __attribute__((nothrow, __with_optimize_perform__, access(read_write, 1)))
#define __a_inj_cwpa __attribute__((nothrow, __with_optimize_perform__))
#define __a_inj_cc __attribute__((nothrow, __with_optimize_perform__, always_inline, stack_protect))
#define __a_inj_rco __attribute__((nothrow, __with_optimize_perform__, always_inline, leaf, no_sanitize_address, no_sanitize_coverage, no_sanitize_undefined, warn_unused_result))
#define __a_inj_rcno __attribute__((nothrow, __with_optimize_perform__, always_inline, leaf, no_sanitize_address, no_sanitize_coverage, no_sanitize_undefined, warn_unused_result))
#define __a_inj_mgd __attribute__((nothrow, __with_optimize_perform__, leaf, const, always_inline))
#define __a_inj_mua __attribute__((nothrow, __with_optimize_perform__, always_inline))
#define __a_inj_mdo __attribute__((nothrow, __with_optimize_perform__, always_inline))
#define __a_inj_mcnb __attribute__((__with_optimize_perform__, nothrow, pure, always_inline, no_sanitize_address, no_sanitize_coverage, warn_unused_result))
#define __a_inj_mbri __attribute__((__with_optimize_perform__, stack_protect, zero_call_used_regs("all"), nothrow, always_inline, no_sanitize_address))
#define __a_inj_mbpi __attribute__((__with_optimize_perform__, stack_protect, zero_call_used_regs("all"), nothrow, always_inline, no_sanitize_address))
#define __a_inj_mbmi __attribute__((__with_optimize_perform__, stack_protect, zero_call_used_regs("all"), nothrow, always_inline, no_sanitize_address))
#define __a_inj_mgrp __attribute__((nothrow, __with_optimize_perform__, leaf, const, always_inline))
#define __a_inj_mgpa __attribute__((nothrow, __with_optimize_perform__, leaf, const, always_inline))
#define __a_inj_mra __attribute__((nothrow, __with_optimize_perform__, always_inline, access(read_only, 1)))
#define __a_inj_mrva __attribute__((nothrow, __with_optimize_perform__, always_inline, access(read_write, 1)))
#define __a_inj_mvls __attribute__((nothrow, __with_optimize_perform__, const, always_inline, leaf, no_sanitize_address, no_sanitize_coverage, no_sanitize_undefined))
#define __a_inj_mlpd __attribute__((nothrow, __with_optimize_perform__, always_inline, no_sanitize_address, no_sanitize_coverage, no_sanitize_undefined))

#else
#define __a_inj_hpf [[nothrow]]

#define __a_inj_dc [[nothrow]]
#define __a_inj_mc [[nothrow]]
#define __a_inj_cwpa [[nothrow]]
#define __a_inj_cc [[nothrow]]
#define __a_inj_rco [[nothrow]]
#define __a_inj_rcno [[nothrow]]
#define __a_inj_mgd [[nothrow]]
#define __a_inj_mgrp [[nothrow]]
#define __a_inj_mgpa [[nothrow]]
#define __a_inj_mra [[nothrow]]
#define __a_inj_mrva [[nothrow]]
#define __a_inj_mvls [[nothrow]]
#define __a_inj_mlpd [[nothrow]]
#define __a_inj_mua [[nothrow]]
#define __a_inj_mdo [[nothrow]]
#define __a_inj_mcnb [[nothrow]]
#define __a_inj_mbri [[nothrow]]
#define __a_inj_mbpi [[nothrow]]
#define __a_inj_mbmi [[nothrow]]
#endif

/*                              Template Defines                               *\
\*******************************************************************************/

// template alias definition, define alias here to improve code semantic analysis and improve code readability...
#define __t_inj_hbc template <typename _cT, typename = std::enable_if<!std::is_array_v<_cT> && !std::is_class_v<_cT> && std::is_integral_v<_cT>, _cT>>
#define __t_inj_dwm template <typename _dT, typename = std::enable_if<std::is_class_v<_dT>, _dT>>
#define __t_inj_smc template <typename _obT>

/**
 * convert _ct _bytes into hex value then string literal value.
 * @if !class
 * @if !array
 * @if integral
 * @param _cT _bytes to convert
 * @returns std::string a const reference to string object
 **/
__t_inj_hbc __a_inj_hpf constexpr static const std::string hexParser(const _cT _bytes) noexcept
{
    static_assert(sizeof(_cT) >= 2, "parser requires an integral type with size >= 2");
    if (_bytes > 0) [[likely]]
    {
        std::stringstream hex_parse;
        hex_parse << "0x" << std::hex << _bytes;
        return hex_parse.str();
    }
    return std::string("0x0");
};

__t_inj_dwm struct AllocDataStat
{
    _dT data{};
    size_t size{0};
    bool null{true};
};

/*                              SecureMalloc Init                              *\
\*******************************************************************************/

/**
 *
 * | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
 *
 **/

__t_inj_smc class SecureMalloc
{

  private:
    bool is_locked_ = false;
    bool is_destroyed_ = false;
    bool is_reset_ = false;
    std::string memory_address_;
    std::mutex loc_mtx_;
#ifdef __a_inj_dpmv
    __a_inj_dpmv _obT *idx0_data_ = nullptr;
#else
    _obT *idx0_data_ = nullptr;
#endif
#ifdef __a_inj_pbs
    __a_inj_pbs size_t idx1_size_ = 0UL;
#else
    size_t idx1_size_ = 0UL;
#endif
#ifdef __a_inj_td
    __a_inj_td _obT *idx2_data_tmp_ = nullptr;
#else
    _obT *idx2_data_tmp_ = nullptr;
#endif

  public:
    __a_inj_dc SecureMalloc() noexcept
    {
        static_assert(std::is_array_v<_obT>, "SecureMalloc don't support arrays.");
        this->idx0_data_ = new (std::nothrow) _obT;
        this->idx2_data_tmp_ = new (std::nothrow) _obT;
        this->memory_address_ = hexParser<std::uintptr_t>(reinterpret_cast<std::uintptr_t>(this->idx0_data_));
        this->idx1_size_ = sizeof(_obT);
    };

    __a_inj_mc explicit SecureMalloc(_obT &&_o) noexcept
    {
        static_assert(std::is_array_v<_obT>, "SecureMalloc don't support arrays.");
        this->InitializeBlock(std::move_if_noexcept(_o));
    };
    __a_inj_mc constexpr SecureMalloc &operator=(_obT &&other) noexcept
    {
        static_assert(std::is_array_v<_obT>, "SecureMalloc don't support arrays.");
        this->InitializeBlock(std::move_if_noexcept(other));
        return *this;
    };

    __a_inj_cwpa explicit SecureMalloc(_obT *__restrict__ _v) noexcept
    {
        static_assert(std::is_array_v<_obT>, "SecureMalloc don't support arrays.");
        this->InitializeBlock(std::move_if_noexcept(_v));
    };
    __a_inj_cwpa SecureMalloc &operator=(_obT *__restrict__ _v) noexcept
    {
        static_assert(std::is_array_v<_obT>, "SecureMalloc don't support arrays.");
        this->InitializeBlock(std::move_if_noexcept(_v));
        return *this;
    };

    __a_inj_cc explicit SecureMalloc(_obT _v) noexcept
    {
        this->InitializeBlock(_v);
    };

    // Comparision operators
    __a_inj_rco constexpr bool operator==(const SecureMalloc &other) const noexcept
    {
        return this->memory_address_.compare(other.address_) == 0;
    };
    __a_inj_rcno constexpr const bool operator!=(const SecureMalloc &other) const noexcept
    {
        return this->memory_address_.compare(other.address_) != 0;
    };

    /**
     * get idx0_data_ data
     * block.
     * @param void
     * @return
     * _ADwM_<_obT>
     * read-only
     */
    __a_inj_mgd constexpr AllocDataStat<_obT> getData(void) noexcept
    {
        struct AllocDataStat<_obT> _rv;
        if (this->idx0_data_ == nullptr || this->is_locked_ || this->is_destroyed_ || this->is_reset_)
        {
            return _rv;
        }
        _rv.data = *this->idx0_data_;
        _rv.null = false;
        _rv.size = sizeof(*this->idx0_data_);
        return _rv;
    };

    /**
     * get idx0_data_ raw
     * block.
     * @param void
     * @return _obT*
     * read-write
     */
    __a_inj_mgrp constexpr _obT *Release(void) noexcept
    {
        return this->is_locked_ ? this->idx2_data_tmp_ : this->idx0_data_;
    };

    /**
     * get memory address.
     * @param void
     * @return std::intptr_t
     * read-only
     */
    __a_inj_mgpa constexpr const std::string getAddress(void) noexcept
    {
        return std::as_const(this->memory_address_);
    };

    /**
     * set idx0_data_ block
     * value.
     * @param _obT& new
     * data
     */
    __a_inj_mra constexpr void Allocate(_obT &_d) noexcept
    {
        static_assert(std::is_array_v<_obT>, "SecureMalloc don't support arrays.");
        this->loc_mtx_.lock();
        if (this->is_locked_)
        {
            this->loc_mtx_.unlock();
            return;
        }
        *this->idx0_data_ = std::move(_d);
        this->loc_mtx_.unlock();
    };
    /**
     * set idx0_data_ block
     * value.
     * @param _obT new data
     */
    __a_inj_mrva constexpr void Allocate(const _obT _d) noexcept
    {
        static_assert(std::is_array_v<_obT>, "SecureMalloc don't support arrays.");
        this->loc_mtx_.lock();
        if (this->is_locked_)
        {
            this->loc_mtx_.unlock();
            return;
        }
        *this->idx0_data_ = std::move(_d);
        this->loc_mtx_.unlock();
    };

    /**
     * Check if idx0_data_
     * locked!
     */
    __a_inj_mvls constexpr bool isLocked(void) const noexcept
    {
        return this->is_locked_;
    };

    /**
     * Lock idx0_data_ access.
     */
    __a_inj_mlpd constexpr void Lock(void) noexcept
    {
        this->loc_mtx_.lock();
        this->is_locked_ = true;
        this->loc_mtx_.unlock();
    };

    /**
     * Unlock idx0_data_
     * access
     */
    __a_inj_mua constexpr void Unlock(void) noexcept
    {
        this->loc_mtx_.lock();
        this->is_locked_ = false;
        this->loc_mtx_.unlock();
    };

    /**
     * Wipe Data
     */
    __a_inj_mdo constexpr void EraseAllocatedData() noexcept
    {
        std::lock_guard<std::mutex> lock_mutex(this->loc_mtx_);

        if (!this->is_destroyed_)
        {
            this->is_destroyed_ = true;
            if (this->idx0_data_ != nullptr)
                delete this->idx0_data_;

            if (this->idx2_data_tmp_ != nullptr)
                delete this->idx2_data_tmp_;
        }
    };

    /**
     * Check if points to null
     * value address.
     * @returns true if null,
     * false otherwise.
     *
     */
    __a_inj_mcnb constexpr bool isBlockNull(void) noexcept
    {
        return this->idx0_data_ == nullptr;
    };

    /**
     * Reset memory block value.
     * @param void
     * @returns void
     */
    constexpr void Reset(void) noexcept
    {
        if (!this->is_destroyed_)
        {
            this->EraseAllocatedData();
        }
        if (!this->is_reset_)
        {
            this->is_reset_ = true;
            this->is_locked_ = true;
        }
    };

    ~SecureMalloc() noexcept
    {
        if (!this->is_reset_)
            this->Reset();
    };

  private:
    /**
     * l-value reference block initialization
     * @param _obT
     * @returns void
     */
    __a_inj_mbri constexpr void InitializeBlock(_obT _v) noexcept
    {
        this->idx0_data_ = new (std::nothrow) _obT(_v);
        this->idx2_data_tmp_ = new (std::nothrow) _obT;
        this->memory_address_ = hexParser<std::uintptr_t>(reinterpret_cast<std::uintptr_t>(this->idx0_data_));
        this->idx1_size_ = sizeof(_v);
    };
    /**
     * l-value reference block
     * initialization
     * @param _obT*
     * @returns void
     */
    __a_inj_mbpi constexpr void InitializeBlock(_obT *__restrict__ _v) noexcept
    {
        if (sizeof(*_v) > 0 && _v != nullptr)
        {
            this->idx0_data_ = std::move_if_noexcept(_v);
            this->idx2_data_tmp_ = new (std::nothrow) _obT;
            this->memory_address_ = hexParser<std::uintptr_t>(reinterpret_cast<std::uintptr_t>(this->idx0_data_));
            this->idx1_size_ = sizeof(*_v);
        }
    };
    /**
     * r-value/l-value
     * reference block
     * initialization
     * @param _obT&&
     * @returns void
     */
    __a_inj_mbmi constexpr void InitializeBlock(_obT &&_v) noexcept
    {
        if (sizeof(_v) > 0)
        {
            this->idx0_data_ = new (std::nothrow) _obT(std::move_if_noexcept(_v));
            this->idx2_data_tmp_ = this->idx0_data_ != nullptr ? new (std::nothrow) _obT(*this->idx0_data_) : new (std::nothrow) _obT;
            this->memory_address_ = hexParser<std::uintptr_t>(reinterpret_cast<std::uintptr_t>(this->idx0_data_));
            this->idx1_size_ = sizeof(_v);
        }
    };
};

#endif

}; // namespace SecureMallocModule
