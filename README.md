# SecureMalloc
Thread-safe memory allocation class providing secure, optimized, and exception-safe memory management with locking, address tracking, and object ownership transfer. Includes methods for allocation, deallocation, locking, unlocking, and address retrieval.


## Description
SecureMalloc provides a secure and thread-safe way to allocate memory for a specific data type T. key details of the class:

* Memory Allocation: The class allocates memory for an object of type T and provides methods for safely accessing and managing the allocated memory.

* Thread Safety: It ensures thread safety by using a mutex (std::mutex) to control access to the allocated memory.

* Memory Address: It stores a unique memory address of the allocated object as a hexadecimal string for identification purposes.

* Locking Mechanism: The class allows locking and unlocking access to the allocated memory to prevent simultaneous modifications by multiple threads.

* Data Management: It provides methods for allocating new data, retrieving data, checking if the memory is locked, and deallocating the memory.

* Comparision Operators: It includes comparison operators (== and !=) to compare memory addresses of two SecureMalloc objects.

* Optimization: The class includes attributes for optimization based on debugging mode, ensuring efficient performance.

* Destructor: The destructor properly deallocates the memory if it has not been previously deallocated.

the class is designed to provide a secure and efficient memory allocation mechanism with thread safety considerations.

# How to Use

### Simple Allocator Instatiator

```cpp
// dont need to include common libraries/headers, SecureMalloc has already access to most of them.
#include "path/to/SecureMalloc.hpp"

int main(int argc, char *argv[]) {
    SecureMalloc<std::string> StrAlloc; // this allocates a string into memory.
    return 0;
};
```

### De-Allocate/Destroy Block

```cpp
    StrAlloc.Deallocate();     // deallocates memory block, will automatically call allocated object destructor.
```


### Get Block Address

```cpp
    std::string get_address = StrAlloc.getAddress();    // get memory location where object/data is stored. You should use direct initialization.
```

### Get Memory Block Data

```cpp
  /**
    * getData will return a structure containing the following entities:
    * -> data(T*)        a pointer to allocated data or nullptr if locked
    * -> null(bool)      true if data is locked
    * -> size(size_t)    the size of the data
    **/
    std::string *get_data = StrAlloc.getData();   // retrieve allocated data with read-write access, returns a pointer to the data
    std::string get_data = *StrAlloc.getData();   // retrieve allocated data with read-only access, data itself.
```

### Lock Memory Block

```cpp
    StrAlloc.Lock();    // locks access to data block.
```

### Unlock Memory Block

```cpp
    StrAlloc.Unlock();    // unlocks access to data block.
```



### Allocate new Data value into Block

```cpp
    StrAlloc.Allocate("another string value");    // allocate new value
```

