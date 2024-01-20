#ifndef S_COBS_H
#define S_COBS_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>

// /**
//  * COBS encode @param src into @param dst
//  */
// size_t cobs_encode (uint8_t *dst, size_t dst_len, uint8_t *src, size_t src_len);

// /**
//  * COBS decode @param src into @param dst
//  */
// size_t cobs_decode (uint8_t *dst, size_t dst_len, uint8_t *src, size_t src_len);

/** COBS encode data to buffer
	@param data Pointer to input data to encode
	@param length Number of bytes to encode
	@param buffer Pointer to encoded output buffer
	@return Encoded buffer length in bytes
	@note Does not output delimiter byte
*/
size_t cobs_encode(const void *data, size_t length, uint8_t *buffer);

/** COBS decode data from buffer
	@param buffer Pointer to encoded input bytes
	@param length Number of bytes to decode
	@param data Pointer to decoded output data
	@return Number of bytes successfully decoded
	@note Stops decoding if delimiter byte is found
*/
size_t cobs_decode(const uint8_t *buffer, size_t length, void *data);

#ifdef __cplusplus
}
#endif
#endif
