# SecureMalloc
Thread-safe memory allocation class providing secure, optimized, and exception-safe memory management with locking, address tracking, and object ownership transfer. Includes methods for allocation, deallocation, locking, unlocking, and address retrieval.


## Description
Secure Memory management utility, allows for secure memory allocation and secure memory DE-allocation. It ensures that data/object gets safely erased from memory as soon as the constructor is called by calling the allocated data object *Destructor* if any or the data only if no object is allocated. The class offers a basic lock/unlock mechanism to ensure at least some control over the memory block data by *locking* the instance and *unlocking* it, when locked, allocated object/data will not be available through the getter which retrieves memory block data living within private regions so cannot be referenced from outside. When used to allocate an entity(object/data) it automatically registers that memory block location into *memory_address* private member variable which can be referrenced from outside with `instance.getAddress()`. for lock/unlock mechanisms it uses a state variable representing lock or unlock state. There is not much you can do with it, just memory allocation/de-allocation in safe mode.


# How to Use

### Simple Allocator Instatiation

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
    std::string get_address = StrAlloc.Deallocate();    // get memory location where object/data is stored. You should use direct initialization.
```

### Get Memory Block Data

```cpp
    std::string *get_data = StrAlloc.getData();   // retrieve allocated data with read-write access control, returns a pointer to the data
    std::string get_data = *StrAlloc.getData();   // retrieve allocated data with read-only access control, data itself.
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

