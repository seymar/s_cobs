#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "../cobs.c"

void printhex (uint8_t *buf, size_t len)
{
    while (len--) printf("%02x ", *buf++);
    printf("\n");
}

void printasc (uint8_t *buf, size_t len)
{
    while (len--) printf("%2c ", *buf++);
    printf("\n");
}

int cmp_arr (uint8_t *a, uint8_t *b, size_t len)
{
    while (len--)
        if (*a++ != *b++) return 0;
    return 1;
}

int main (int argc, char **argv)
{
    char in[] = "bla\nbla\n";
    printf("original: %zu\n", sizeof(in));
    printhex((uint8_t*)in, sizeof(in));
    printasc((uint8_t*)in, sizeof(in));

    uint8_t out1[2*sizeof(in)] = {0};
    size_t n1 = cobs_encode(out1, sizeof(out1), (uint8_t*)in, sizeof(in));
    printf("encoded: %zu\n", n1);
    printhex((uint8_t*)out1, n1);
    printasc((uint8_t*)out1, n1);

    uint8_t out2[10] = {0};
    size_t n2 = cobs_decode(out2, sizeof(out2), out1, n1);
    printf("decoded: %zu\n", n2);
    printhex((uint8_t*)out2, n2);
    printasc((uint8_t*)out2, n2);

    printf("TESTCASE: in len matches out len\n");
    if (sizeof(in) == n2) {
        printf("  PASS ");
    } else {
        printf("  FAIL ");
        exit(1);
    }
    printf("sizeof(in) == n2\n");
    
    printf("TESTCASE: decoded matches original\n");
    if (cmp_arr((uint8_t *)in, out2, sizeof(in)) == 1) {
        printf("  PASS ");
    } else {
        printf("  FAIL ");
        exit(1);
    }
    printf("bla\\nbla\\n\n");
}
