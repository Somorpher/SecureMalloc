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

#ifndef __UNIT_SAFE_MEMORY_ALLOC__
#define __UNIT_SAFE_MEMORY_ALLOC__

// if macro "IS_DEBUGGING_CODE" is found somewhere in the scope, then optimize = 0
#ifdef IS_DEBUGGING_CODE
#define __with_optimize_perform__ optimize("0")
#else
#define __with_optimize_perform__ optimize("3")
#endif

#if defined(__GNUC__) || defined(__clang__)
#define __hex_parser_attr__ __attribute__((pure, nothrow, always_inline, no_icf, stack_protect, optimize("2"), tainted_args))
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

template <typename TX> struct xValue {
    TX* data{nullptr};
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

  public:
    __attribute__((mode(__pointer__))) T *data_ = nullptr;

  private:
    __attribute__((mode(__word__))) size_t size_ = 0UL;
    __attribute__((mode(__pointer__))) T *data_tmp_ = nullptr;

  public:
    __attribute__((nothrow, __with_optimize_perform__)) SecureMalloc() noexcept
    {
        this->data_ = new (std::nothrow) T;
        this->data_tmp_ = this->data_ != nullptr ? new (std::nothrow) T(*this->data_) : new (std::nothrow) T;
        std::uintptr_t addr_ptr = reinterpret_cast<std::uintptr_t>(this->data_);
        this->memory_address_ = hexParser<std::uintptr_t>(addr_ptr);
        this->size_ = sizeof(T);
    };

    __attribute__((nothrow, __with_optimize_perform__, access(read_only, 1))) explicit SecureMalloc(const T &_v) noexcept
    {
        this->CommonInitialization(std::move(_v));
    };

    __attribute__((nothrow, __with_optimize_perform__, access(read_only, 1))) explicit SecureMalloc(const T &&_v) noexcept
    {
        this->CommonInitialization(std::move(_v));
    };

    /**
     * get data_ section.
     * @param void
     * @return T* read-write access to private data member pointer
     */
    __attribute__((nothrow, __with_optimize_perform__, leaf, const, always_inline)) inline xValue<T> getData(void) noexcept
    {
        struct xValue<T> _rv;
        if(this->data_ == nullptr || this->locked_){
            return _rv;
        }
        _rv.data = this->data_;
        _rv.null = false;
        _rv.size = sizeof(*this->data_);
        return _rv;        
    };

    /**
     * get memory address data section.
     * @param void
     * @return std::intptr_t read-only access to private data member pointer address_
     */
    __attribute__((nothrow, __with_optimize_perform__, leaf, const, always_inline)) inline const std::string getAddress(void) noexcept
    {
        return std::as_const(this->memory_address_);
    };

    /**
     * set data_ section.
     * @param T& new data
     */
    __attribute__((nothrow, __with_optimize_perform__, always_inline)) inline void Allocate(T &_d) noexcept
    {
        this->loc_mtx_.lock();
        if (this->locked_)
        {
            this->loc_mtx_.unlock();
            return;
        }
        *this->data_ = std::move(_d);
        this->loc_mtx_.unlock();
    };

    /**
     * Check if data_ section is locked_!
     */
    __attribute__((nothrow, __with_optimize_perform__, const, always_inline, leaf, no_sanitize_address, no_sanitize_coverage, no_sanitize_undefined)) inline const bool isLocked(void) const noexcept
    {
        return this->locked_;
    };

    /**
     * Lock Access to data_ section.
     */
    __attribute__((nothrow, __with_optimize_perform__, always_inline, no_sanitize_address, no_sanitize_coverage, no_sanitize_undefined)) inline void Lock(void) noexcept
    {
        this->loc_mtx_.lock();
        this->locked_ = true;
        this->loc_mtx_.unlock();
    };

    /**
     * Unlock access to data_ section
     */
    __attribute__((nothrow, __with_optimize_perform__, always_inline)) inline void Unlock(void) noexcept
    {
        this->loc_mtx_.lock();
        this->locked_ =false;
        this->loc_mtx_.unlock();
    };

    SecureMalloc(const SecureMalloc &) noexcept = delete;
    SecureMalloc(const SecureMalloc &&other) noexcept : data_(std::exchange(other.data_)), size_(other.size_), locked_(other.locked_) {};
    SecureMalloc &operator=(const SecureMalloc &) noexcept = delete;
    SecureMalloc &operator=(const SecureMalloc &&) noexcept = delete;

    __attribute__((nothrow, __with_optimize_perform__, always_inline, leaf, no_sanitize_address, no_sanitize_coverage, no_sanitize_undefined, warn_unused_result)) inline const bool &operator==(
        const SecureMalloc &other) const noexcept
    {
        return this->memory_address_.compare(other.address_) == 0;
    };

    /**
     * Wipe Data slots
     */
    __attribute__((nothrow, __with_optimize_perform__, always_inline)) inline void Deallocate() noexcept
    {
        this->loc_mtx_.lock();
        if (this->erased_ == false)
        {
            this->erased_ = true;
            if (this->data_ != nullptr)
                delete this->data_; // calls the destructor of data_ object

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
    __attribute__((__with_optimize_perform__, nothrow, pure, always_inline, no_sanitize_address, no_sanitize_coverage, warn_unused_result)) inline const bool PtrNullValue(void) noexcept
    {
        return this->data_ == nullptr;
    };

    ~SecureMalloc() noexcept
    {
        if (!this->erased_)
            this->Deallocate();
    };

  private:
    __attribute__((__with_optimize_perform__, stack_protect, zero_call_used_regs("all"), nothrow, always_inline, no_sanitize_address)) inline void CommonInitialization(T &_v) noexcept
    {
        if (sizeof(_v) > 0)
        {
            this->data_ = new (std::nothrow) T(std::exchange(_v));
            this->data_tmp_ = this->data_ != nullptr ? new (std::nothrow) T(*this->data_) : new (std::nothrow) T;
            std::uintptr_t addr_ptr = reinterpret_cast<std::uintptr_t>(this->data_);
            this->memory_address_ = hexParser<std::uintptr_t>(addr_ptr);
            this->size_ = sizeof(_v);
        }
    };
};

#endif
