#include <stdio.h>
#include "functions.c" 

int main(void)
{
    struct space mem;

    printf("Initialising 20 cells of memory:\n");
    initialiseMemory(20, &mem);

    printf("\nAllocating block A (5 bytes):\n");
    int a = heapAllocator(5, &mem);
    printMemory(&mem);

    printf("\nAllocating block B (4 bytes):\n");
    int b = heapAllocator(4, &mem);
    printMemory(&mem);

    printf("\nFreeing block A:\n");
    deallocator(a, &mem);
    printMemory(&mem);

    printf("\nAllocating block C (3 bytes) which reuses A's space:\n");
    int c = heapAllocator(3, &mem);
    printMemory(&mem);

    printf("\nAllocating block D (15 bytes) which forces memory to grow:\n");
    int d = heapAllocator(15, &mem);
    printMemory(&mem);

    printf("\nCleaning up:\n");
    cleanMemory(&mem);

    printf("\nDone :)\n");
    return 0;
}
