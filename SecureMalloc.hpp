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

// for converting uintptr_t to hex as string
template <typename T> const std::string hexParser(const T _bytes) noexcept
{
     if (sizeof(_bytes) > 0) [[likely]]
    {
        std::stringstream hex_parse;
        hex_parse << "0x" << std::hex << _bytes;
        return hex_parse.str();
    }
    return "0x0";
};


template <typename T> class SecureMalloc
{

  private:
    bool locked_ = false;
    bool erased_ = false;
    std::string memory_address_;

    public: __attribute__((mode(__pointer__))) T *data_ = nullptr;
    private: __attribute__((mode(__word__))) size_t size_ = 0UL;
    __attribute__((mode(__pointer__))) T *data_tmp_ = nullptr;

  public:
    __attribute__((nothrow, __with_optimize_perform__)) SecureMalloc() noexcept
    {
        this->data_ = new (std::nothrow) T;
        this->data_tmp_ = new(std::nothrow) T(*this->data_);
        std::uintptr_t addr_ptr = reinterpret_cast<std::uintptr_t>(this->data_);
        this->memory_address_ = hexParser<std::uintptr_t>(addr_ptr);
        this->size_ = sizeof(T);
    };

    __attribute__((nothrow, __with_optimize_perform__, access(read_only, 1))) explicit SecureMalloc(const T &_v) noexcept
    {
        if (sizeof(_v) > 0)
        {
            this->data_ = new (std::nothrow) T(std::exchange(_v));
            this->data_tmp_ = new(std::nothrow) T(*this->data_);
            std::uintptr_t addr_ptr = reinterpret_cast<std::uintptr_t>(this->data_);
            this->memory_address_ = hexParser<std::uintptr_t>(addr_ptr);
            this->size_ = sizeof(_v);
        }
    };

    __attribute__((nothrow, __with_optimize_perform__, access(read_only, 1))) explicit SecureMalloc(const T &&_v) noexcept
    {
        if (sizeof(_v) > 0)
        {
            this->data_ = new (std::nothrow) T(std::move(_v));
            this->data_tmp_ = new(std::nothrow) T(*this->data_);
            std::uintptr_t addr_ptr = reinterpret_cast<std::uintptr_t>(this->data_);
            this->memory_address_ = hexParser<std::uintptr_t>(addr_ptr);
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
        return this->locked_ ? nullptr : this->data_;
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
        if (this->locked_)
            return;
        *this->data_ = std::move(_d);
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
        this->locked_ = true;
        *this->data_tmp_ = *this->data_;
        delete this->data_;
        this->data_ = nullptr;
    };

    /**
     * Unlock access to data_ section
     */
    __attribute__((nothrow, __with_optimize_perform__, always_inline, no_sanitize_address, no_sanitize_coverage, no_sanitize_undefined)) inline void Unlock(void) noexcept
    {
        this->locked_ = false;
        *this->data_ = *this->data_tmp_;
        delete this->data_tmp_;
        this->data_tmp_ = nullptr;
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
     * Clean Data.
     */
    __attribute__((nothrow, __with_optimize_perform__, always_inline, no_sanitize_address, no_sanitize_coverage, no_sanitize_undefined)) inline void Deallocate() noexcept
    {
        if (!this->erased_)
        {
            this->erased_ = true;
            if (this->data_ != nullptr)
                delete this->data_; // calls the destructor of data_ object

            if (this->data_tmp_ != nullptr)
                delete this->data_tmp_;
        }
    }

    ~SecureMalloc() noexcept
    {
        this->Deallocate();
    };
};

#endif
