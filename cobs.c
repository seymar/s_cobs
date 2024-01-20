#include <assert.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

#define DELIM '\n'

size_t cobs_encode (uint8_t *dst, size_t dst_len, uint8_t *src, size_t src_len)
{
    ///WARNING: Only space for 1 overhead byte is asserted
    assert(dst_len > src_len);
    assert(dst != NULL);
    assert(src != NULL);

    if (src_len == 0) return 0; // nothing to encode

    uint8_t *ptr = dst + 1;
    uint8_t *ohb = dst;
    uint8_t *src_end = src + src_len;
    uint8_t n = 0, c = 0;
    for (;;) {
        c = *src++;
        if (c == DELIM) {
            if (n >= DELIM) n++;
            *ohb = n;
            ohb = ptr++;
            n = 0;
        } else {
            *ptr++ = c;
            n++;
        }
        if (src >= src_end) break; // done
        if (n == 255) { // n > 255
            *ptr++ = n;
            n = 1;
        }
    }
    *ohb = n;
    return ptr - dst;
}

size_t cobs_decode (uint8_t *dst, size_t dst_len, uint8_t *src, size_t src_len)
{
    assert(dst_len >= src_len - 1);
    assert(dst != NULL);
    assert(src != NULL);

    if (src_len == 0) return 0; // nothing to decode

    uint8_t *ptr = dst;
    uint8_t *src_end = src + src_len;
    uint8_t n = *src, c = 0;
    src++;
    for (;;) {
        c = *src++;
        if (c == DELIM) return 0;
        if (n == 0) {
            if (c > DELIM) c--;
            n = c;
            *ptr++ = DELIM;
        } else {
            *ptr++ = c;
            n--;
        }
        if (src >= src_end) break; // done
    }
    return ptr - dst;
}