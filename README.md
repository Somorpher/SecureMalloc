# SecureMalloc

> Type = Module

The Malloc class is a thread-safe, low-level memory management utility that provides a safe and efficient way to allocate and deallocate memory blocks of a specified type _cT, while preventing common memory-related issues such as memory leaks, dangling pointers, and data corruption, and offering various methods for allocation, deallocation, and introspection, including constructor overloads for default, copy, move, and value initialization, assignment operators, comparision operators, getters for block address and size, allocation and deallocation methods, and a destructor for automatic cleanup.

## Note:
the class is not meant to work with the following types:

* arrays(int[], char[], string[], some_obj[], etc..)
* non trivially copyable objects
* object requiring constructor arguments 


# How to Use

### basic Instatiation

```cpp
#include "path/to/SecureMalloc.hpp"
int main(int argc, char *argv[]) {
    SecureMalloc<std::string> StrAlloc; // this allocates a new string space block
    return 0;
};
```

### Allocate new Data
> allocate new data
```cpp
    StrAlloc.Alloc("another string value");
```

### De-Allocate/Destroy Block
> wipe/erase/delete/deallocate allocated block
```cpp
    // deallocates memory block, will automatically call allocated object destructor if any.
    StrAlloc.Free();
```


### Get Address space
> get the allocation address
```cpp
    // get memory location where object/data is stored as hex.
    std::uintptr_t = StrAlloc.GetAddress();
```

### Get allocated data
> Get Allocated data either allocated by a constructor or Allocate method.
```cpp
    std::string get_data = *StrAlloc.Get();
```

### Simple Implementation
> here using string, but any type will be ok, read the "Note" section for more info.
```cpp
#require "path/to/SecureAlloc.hpp"

int main() {

    SecureAlloc<std::string> str_alloc; // empty initialization, call default constructor
    SecureAlloc<std::string> str_alloc_2("some string"); // direct initialization with data allocation

    std::cout << "Allocated Value: " << *str_alloc_2.Get() << "\n";
    std::cout << "Allocated Address: " << str_alloc_2.GetAddress() << "\n";
    std::cout << "Allocated Size: " << str_alloc_2.GetSize() << "\n";
    std::cout << "Is Alloc Null: " << std::boolalpha << str_alloc_2.IsNullPtr() << "\n";

    str_alloc_2.Free(); // release allocated

    return 0;
}
```
