
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdint.h>

void test_basic()
{
    void* p = malloc(100);
    if (!p) {
        write(1, "FAIL basic alloc\n", 17);
        return;
    }

    free(p);
    write(1, "OK basic\n", 9);
}


void test_write()
{
    char* p = (char*)malloc(50);

    for (int i = 0; i < 50; i++)
        p[i] = i;

    for (int i = 0; i < 50; i++)
    {
        if (p[i] != i)
        {
            write(1, "FAIL write\n", 11);
            return;
        }
    }

    free(p);
    write(1, "OK write\n", 9);
}


void test_many_allocs()
{
    void* arr[1000];

    for (int i = 0; i < 1000; i++)
        arr[i] = malloc(32);

    for (int i = 0; i < 1000; i++)
        free(arr[i]);

    write(1, "OK many allocs\n", 15);
}


void test_reuse()
{
    void* p1 = malloc(100);
    free(p1);

    void* p2 = malloc(100);

    if (p1 == p2)
        write(1, "OK reuse\n", 9);
    else
        write(1, "WARN no reuse\n", 14);

    free(p2);
}


void test_coalesce()
{
    void* p1 = malloc(100);
    void* p2 = malloc(100);

    free(p1);
    free(p2);

    void* p3 = malloc(180);

    if (p3 == p1)
        write(1, "OK coalesce\n", 12);
    else
        write(1, "FAIL coalesce\n", 14);

    free(p3);
}


void test_mmap()
{
    void* p = malloc(200 * 1024);

    if (!p)
    {
        write(1, "FAIL mmap alloc\n", 16);
        return;
    }

    free(p);
    write(1, "OK mmap\n", 8);
}

void test_split()
{
    void* p1 = malloc(1000);
    free(p1);

    void* p2 = malloc(100);

    // если split работает — не должен вызывать sbrk снова
    write(1, "Check split manually (splited msg)\n", 36);

    free(p2);
}

void test_mixed()
{
    void* a = malloc(64);
    void* b = malloc(200000); // mmap
    void* c = malloc(128);

    free(a);
    free(c);
    free(b);

    write(1, "OK mixed\n", 9);
}

int main()
{
    test_basic();
    test_write();
    test_many_allocs();
    test_reuse();
    test_split();
    test_coalesce();
    test_mmap();
    test_mixed();

    return 0;
}