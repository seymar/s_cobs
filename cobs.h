#ifndef S_COBS_H
#define S_COBS_H

#include <stdint.h>
#include <stddef.h>

/**
 * COBS encode @param src into @param dst
 */
size_t cobs_encode (uint8_t *dst, size_t dst_len, uint8_t *src, size_t src_len);

/**
 * COBS decode @param src into @param dst
 */
size_t cobs_decode (uint8_t *dst, size_t dst_len, uint8_t *src, size_t src_len);

#endif
