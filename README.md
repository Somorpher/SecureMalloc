# SecureMalloc Module

> Type = Module

### Module
The SecureMalloc module is a high-performance memory allocation class designed to provide secure and optimized memory management for a specific data type T. This module utilizes various optimization attributes to achieve exceptional performance, security, and reliability.
The SecureMalloc class is a thread-safe memory allocation class that provides secure, optimized, and exception-safe memory management with locking, address tracking, and object ownership transfer. The class ensures proper memory deallocation and includes methods for allocation, deallocation, locking, unlocking, and address retrieval.

### Optimization
The SecureMalloc class achieves optimization through the use of various attributes and techniques that improve performance, security, and reliability.


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

### basic Instatiation

```cpp
#include "path/to/SecureMalloc.hpp"

using namespace SecureMallocModule; // access to module

int main(int argc, char *argv[]) {
    SecureMalloc<std::string> StrAlloc; // this allocates a string into memory.
    return 0;
};
```

### Allocate new Data
> allocate new block of data
```cpp
// allocate new value, this will move data and transfer ownership,
// good for cases where data being allocated does not support copy operations
    StrAlloc.Allocate("another string value");
```

### De-Allocate/Destroy Block
> wipe/erase/delete/deallocate allocated block
```cpp
    StrAlloc.Deallocate();     // deallocates memory block, will automatically call allocated object destructor.
```


### Get allocated Address
> get the address where the block was allocated

```cpp
    std::string get_address = StrAlloc.getAddress();    // get memory location where object/data is stored. You should use direct initialization.
```

### Get allocated data
> Get Allocated data either allocated by a constructor or Allocate method.
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
> lock memory block, if already locked, will have no effect.
```cpp
    StrAlloc.Lock();    // locks access to data block.
```

### Unlock Memory Block
> unlock memory block, if already unlocked, will have no effect.
```cpp
    StrAlloc.Unlock();    // unlocks access to data block.
```

### Simple Implementation
> object type allocation example
```cpp
// include headers, main, etc...

    std::vector<int> IV; // vector of interest

    SecureMalloc<std::vector<int>> V(IV); // alloc space

    SafeDataAccess get_iv = V.getData(); // get allocated block

    // check if data is unlocked and accessible
    std::cout << "Before Locking Data:\n";
    if (!V.getData().null)
    {
        std::cout << "Data Is Accessible..\n";
        std::cout << "Vector Size: " << V.getData().data.size() << '\n';
    }

    // lock access, from here, until access is locked, no write operations will have effect
    // if try to write to memory location where data is stored, it will not raise any error, but
    // will instead write to a tmp object created for this scenario.
    V.Lock();

    std::cout << "After Locking Data:\n";

    if (!V.getData().null)
        std::cout << "Data Is Accessible..\n";
    else
        std::cout << "Data Is Locked!\n";

    V.getRawPtr()->push_back(1); // will not have any effect other than writing to a tmp object(T)

    std::cout << "Vector Size After push(Locked):   " << V.getData().data.size() << '\n';

    V.Unlock(); // unlock address

    V.getRawPtr()->push_back(1); // this will write to data!

    std::cout << "Vector Size After push(Unlocked): " << V.getData().data.size() << '\n';

    V.Deallocate(); // deallocation is optional...
```

## Warning:

this wont work with C style arrays like "int[1] or char[1]".
