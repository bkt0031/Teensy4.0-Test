#ifndef STRING_UTILITIES_H
#define STRING_UTILITIES_H

#include <stdint.h>
#include <stdbool.h>

#define UINT32_T_BASE_SIZE (1000000000u)
#define UINT32_T_MAX_DIGITS ( 10u )
#define UINT16_T_BASE_SIZE (10000u)
#define UINT16_T_MAX_DIGITS ( 5u )
#define UINT8_T_BASE_SIZE (100u)
#define UINT8_T_MAX_DIGITS ( 3u )

char *uint32_to_str(uint32_t n, char *s, uint8_t len, bool pad_leading);
char *uint16_to_str(uint16_t n, char *s, uint8_t len, bool pad_leading);
char *int16_to_str(int16_t n, char *s, uint8_t len, bool pad_leading);
char *uint8_to_str(uint8_t n, char *s, uint8_t len, bool pad_leading);

#endif