#include <assert.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

/** COBS encode data to buffer
	@param data Pointer to input data to encode
	@param length Number of bytes to encode
	@param buffer Pointer to encoded output buffer
	@return Encoded buffer length in bytes
	@note Does not output delimiter byte
*/
size_t cobs_encode(const void *data, size_t length, uint8_t *buffer)
{
	assert(data && buffer);

	uint8_t *encode = buffer; // Encoded byte pointer
	uint8_t *codep = encode++; // Output code pointer
	uint8_t code = 1; // Code value

	for (const uint8_t *byte = (const uint8_t *)data; length--; ++byte)
	{
		if (*byte) // Byte not zero, write it
			*encode++ = *byte, ++code;

		if (!*byte || code == 0xff) // Input is zero or block completed, restart
		{
			*codep = code, code = 1, codep = encode;
			if (!*byte || length)
				++encode;
		}
	}
	*codep = code; // Write final code value

	return (size_t)(encode - buffer);
}

/** COBS decode data from buffer
	@param buffer Pointer to encoded input bytes
	@param length Number of bytes to decode
	@param data Pointer to decoded output data
	@return Number of bytes successfully decoded
	@note Stops decoding if delimiter byte is found
*/
size_t cobs_decode(const uint8_t *buffer, size_t length, void *data)
{
	assert(buffer && data);

	const uint8_t *byte = buffer; // Encoded input byte pointer
	uint8_t *decode = (uint8_t *)data; // Decoded output byte pointer

	for (uint8_t code = 0xff, block = 0; byte < buffer + length; --block)
	{
		if (block) // Decode block byte
			*decode++ = *byte++;
		else
		{
			block = *byte++;             // Fetch the next block length
			if (block && (code != 0xff)) // Encoded zero, write it unless it's delimiter.
				*decode++ = 0;
			code = block;
			if (!code) // Delimiter code found
				break;
		}
	}

	return (size_t)(decode - (uint8_t *)data);
}

#if 0
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
        c = *src++; // get byte from source
        if (c == DELIM) { // if byte is equal to delimiter
            if (n >= DELIM) n++;
            *ohb = n; // set previous overhead byte to current number of bytes
            ohb = ptr++; // create new overhead byte at current byte
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
#endif
