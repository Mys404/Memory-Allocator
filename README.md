# Memory-Allocator
This is a small memory allocator, I made in C for a university project.

# What it does
The program shows how memory can be allocated and freed in C. It keeps a track of which parts of memory are being used and which parts are free. It can also reuse memory that has been freed and increase the amount of memory available when more space is needed. 

# How it works
First, a set amount of memory is created and tracked using two arrays. The 'memory' array keeps a track of which parts are 'BUSY' and which are 'FREE', while the 'sizes' array keeps a track of the size of each allocation.

 - `heapAllocator()` - Looks for free space and marks it as busy
 - `deallocator()` - Frees an allocated block, so that its space can be used again
 - `increaseMemory()` - If there isn't enough free space, the amount of memory available is increased and the existing memory is copied over
   
`main.c` starts off with 20 cells of memory and allocates a few blocks of memory (block A and block B). It then frees one of the memory blocks and makes a smaller allocation that reuses the freed space. After this, it makes a larger allocation that cannot fit into the available space, which then calls the `increaseMemory()` function to increase the amount of memory available.

# How to run
```
gcc main.c -o main
./main
```
