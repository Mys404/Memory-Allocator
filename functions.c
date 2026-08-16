#include <stdlib.h>
#include <stdio.h>

#define BUSY '+'
#define FREE '_'
#define BUSYSIZE -1
#define FREESIZE 0

struct space
{
    char *memory;
    int *sizes;
    int len;
};

void printMemory(struct space *mem)
{
    int i = 0;
    while (i < mem->len)
    {
        printf("%c", *(mem->memory + i));
        i = i + 1;
    }
    printf("\n");
}

void printSizes(struct space *mem)
{
    int i = 0;
    int c;
    while (i < mem->len)
    {
        int n = *(mem->sizes + i);
        int t = 10000;
        while (n > 9)
        {
            c = n / t;
            n = n - c * t;
            t = t / 10;
            if (c)
            {
                c = c % 10 + '0';
                printf("%c", c);
                i = i + 1;
            }
        }
        c = n % 10 + '0';
        printf("%c", c);
        i = i + 1;
    }
    printf("\n");
}

void copyString(char *sIn, char *sOut, int len)
{
    int t = 0;
    while (t < len)
    {
        *(sOut + t) = *(sIn + t);
        t = t + 1;
    }
}
int stringLen(char *s)
{
    int t = 0;
    while (*(s + t) != '\0')
        t++;
    return t;
}
void copyArray(int *oldArray, int *newArray, int len) // function allows to copy an array of int values
{
    int t = 0;
    //copies elements from the old array into the new array
    while (t < len)
    {
        *(newArray + t) = *(oldArray + t);
        t = t + 1;
    }
}

void initialiseMemory(int memSize, struct space *mem) // initialises memory space
{
    //allocates memory for the memory block and thier sizes
    mem->memory = (char *)malloc(memSize * sizeof(char));
    mem->sizes = (int *)malloc(memSize * sizeof(int));

    //sets the total memory length
    mem->len = memSize;

    //intialises memory blocks to free and sets the sizes to FREESIZE
    for (int i = 0; i < memSize; i++)
    {
        mem->memory[i] = FREE;
        mem->sizes[i] = FREESIZE;
    }

    //prints the memory and sizes
    printMemory(mem);
    printSizes(mem);
}

void cleanMemory(struct space *mem) //cleans up and frees the memory space
{
    //set all memory blocks to free and thier size to FREESIZE
    for (int i = 0; i < mem->len; i++)
    {
        mem->memory[i] = FREE;
        mem->sizes[i] = FREESIZE;
    }

    //prints the memory and sizes
    printMemory(mem);
    printSizes(mem);

    //frees the allocated memory
    free(mem->memory);
    free(mem->sizes);
}

void deallocator(int t0, struct space *mem) //deallocates memory blocks
{
    if (t0 >= mem->len || t0 < 0)
    {
        return;
    }

    //chooses if the size of the block should be deallocated
    int nbytes = mem->sizes[t0];
    int t = 0;

    //marks the block as free and the sizes as FREESIZE
    while (t < nbytes)
    {
        if ((t0 + t) < mem->len)
        {
            mem->memory[t0 + t] = FREE;
            mem->sizes[t0 + t] = FREESIZE;
        }
        t++;
    }
}

int spaceScanner(int nbytes, struct space *mem) //scans for a block of free memory with the wanted size
{
    int t0 = 0;
    int s = 0;
    //scans for a block of free memory with the wanted size
    while (s == 0 && t0 < mem->len)
    {
        int t = 0;

        //checks for continous free space
        while ((t0 + t < mem->len) && (mem->sizes[t0 + t] == FREESIZE))
        {
            t++;
        }

        //checks if the space is enough
        if (t >= nbytes)
        {
            s = 1;
            break;
        }

        else
        {
            t0++;
        }
    }

    //returns the starting index of the new space or the memory length if no space is found
    return t0;
}


void increaseMemory(int nbytes, struct space *mem) //increases total memory size
{
    int t = mem->len;

    //increases the total memory size
    while ((t - mem->len) < nbytes)
    {
        t = 2 * (t + 1);
    }

    //saves the current memory and size arrays
    char *s = mem->memory;
    int *a = mem->sizes;
    int l = mem->len;

    //initialises the new larger memory
    initialiseMemory(t, mem);

    //copes old memory and size into the new memory
    copyString(s, mem->memory, l);
    copyArray(a, mem->sizes, l);

    //frees old memory
    free(s);
    free(a);
}

int heapAllocator(int nbytes, struct space *mem) //allocates a block of memory
{
    //scans to find a free block of memory with the right amount of space
    int t0 = spaceScanner(nbytes, mem);

    //if theres no suitable memory block found, it increases the memory size until it finds one
    while (t0 == mem->len)
    {
        increaseMemory(nbytes, mem);
        t0 = spaceScanner(nbytes, mem);
    }

    //marks the found block as busy and sets its size to BUSYSIZE
    for (int t = 0; t < nbytes; t++)
    {
        mem->memory[t0 + t] = BUSY;

        mem->sizes[t0 + t] = (t == 0) ? nbytes : BUSYSIZE;
    }

    //sets the actual size at the beginning of the memory block
    mem->sizes[t0] = nbytes;
    //returns the starting index of the allocated block
    return t0;
}

int readString(char **s) //allows to read and store a string from input
{
    //reads the first character
    int t = 0;
    char c = getchar();

    //allocates memory for the string (1 byte)
    *s = (char *)malloc(1);
    //sets to an empty string
    **s = '\0';

    //reads charecters until theres a newline or EOF
    while (c != '\n' && c != EOF)
    {
        //allocates memory for the new size
        char *p = *s;
        t++;
        *s = (char *)malloc(t + 1);

        //copies the old string into the new memory
        for (int i = 0; i < t - 1; i++)
        {
            (*s)[i] = p[i];
        }
        //frees the old memory
        free(p);
        //adds the new character to the string
        (*s)[t - 1] = c;
        //null terminates the string and reads the next charecter
        (*s)[t] = '\0';
        c = getchar();
    }
    //if EOF is activated, it will return 0. Otherwise returns 1
    if (c == EOF)
    {
        return 0;
    }

    return 1;
}
