# Command Line
Command Line (CL) library - providing line edit functionality for bare metal systems.


A minimal, zero-config, GPL licensed, readline replacement.

Line editing with support for history is important feature for command line editing over serial connection. The focus of this library is to provide this functionality for bare metal systems assuming only C compiler is available. The library comes with its own implementation of string manipulation functions and doesn't require standard C library.

# The API
    int cl_mem_init(void *pAddr, unsigned int uSize, unsigned int uBlocks);
    int cl_history_init();
    int cl_editline(const char *pszPrompt, char *pszBuffer, unsigned int uBufferSize, unsigned int uHistoryEntries);


CL is very easy to use. cl_editline returns the size of the line in the provided buffer, it takes 3 parameters:
 * pszPrompt is the prompt that will apear on the terminal.
 * pszBuffer is the memory pointer where the final line will be constructed.
 * uSize is the size of the buffer.
 * uHistoryEntries is the number of history entries you wish to maintain.


# Example 1:

    char Heap[4096];
    char szBuffer[1024];
    cl_mem_init(Heap, sizeof(Heap), 100);
    cl_history_init();
    while (1) {
      if (cl_editline("# ", szBuffer, sizeof(szBuffer), 5) > 0)
        printf("\r\nYou wrote: %s", szBuffer);

      printf("\r\n");
    }

The use of cl_mem_init is needed only if you don't have your own dynamic memory allocation mechanism. If the
malloc/free functions are available, you can simply compile with CL_HAS_MALLOC defined. Then the code will be even simpler.

# Example 2:

    char szBuffer[1024];
    cl_history_init();
    while (1) {
      if (cl_editline("# ", szBuffer, sizeof(szBuffer), 5) > 0)
        printf("\r\nYou wrote: %s", szBuffer);

      printf("\r\n");
    }

## Porting to new system
There are only 4 functions in the 'ClPort.c' file that might need to be changed to start using the library in your environment.

    int cl_putchar(int c);
    int cl_getchar();
    void *cl_mem_alloc(unsigned int uSize);
    void cl_mem_free(void *pAddr);

Basically, all you need to do is:
1. Reimplement the cl_putchar/cl_getchar to work on your device.
2. If you already have a dynamic memory allocation mechanism you can reimplement cl_mem_alloc/cl_mem_free. If you don't you can just initialize its own heap allocator as shown in the Example 1. If you have access malloc/free all you need to do is compile with "#define CL_HAS_MALLOC". When CL_HAS_MALLOC is defined cl_mem_init() is not availabe, you should look at example 2 how to use the library in that case.

