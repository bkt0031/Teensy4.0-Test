#include "string_utilities.h"

char *uint32_to_str(uint32_t n, char *s, uint8_t len, bool pad_leading) {
  uint32_t digit = UINT32_T_BASE_SIZE;
  uint32_t total_digits = UINT32_T_MAX_DIGITS;
  uint8_t npad = 0u;

  if (len > 0) {
    if (n > 0) {
      while (digit > n) {
        digit /= 10;
        --total_digits;
      }
    } else {
      digit = 1;
      total_digits = 1;
    }
    if (total_digits > len) {
      for (uint8_t i = 0; i < len; i++)
        *s++ = '-';
    } else {
      if (total_digits < len && pad_leading) {
        npad = len - total_digits;
        for (uint8_t i = 0; i < npad; i++)
          *s++ = '0';
      }
      do {
        *s++ = '0' + (n - n % digit) / digit % 10;
      } while (digit /= 10);
    }
  }
  *s = '\0';
  return s;
}

char *uint16_to_str(uint16_t n, char *s, uint8_t len, bool pad_leading) {
  uint16_t digit = UINT16_T_BASE_SIZE;
  uint32_t total_digits = UINT16_T_MAX_DIGITS;
  uint8_t npad = 0u;

  if (len > 0) {
    if (n > 0) {
      while (digit > n) {
        digit /= 10;
        --total_digits;
      }
    } else {
      digit = 1;
      total_digits = 1;
    }
    if (total_digits > len) {
      for (uint8_t i = 0; i < len; i++)
        *s++ = '-';
    } else {
      if (total_digits < len && pad_leading) {
        npad = len - total_digits;
        for (uint8_t i = 0; i < npad; i++)
          *s++ = '0';
      }
      do {
        *s++ = '0' + (n - n % digit) / digit % 10;
      } while (digit /= 10);
    }
  }
  *s = '\0';
  return s;
}

char *int16_to_str(int16_t n, char *s, uint8_t len, bool pad_leading) {
  uint8_t nchars = 0u;

  if (len > 0) {
    if (n < 0) {
      *s++ = '-';
      n = -n;
      ++nchars;
    }
    s = uint16_to_str((uint16_t)n, s, len - nchars, pad_leading);
  }
  return s;
}

char *uint8_to_str(uint8_t n, char *s, uint8_t len, bool pad_leading) {
  uint8_t digit = UINT8_T_BASE_SIZE;
  uint32_t total_digits = UINT8_T_MAX_DIGITS;
  uint8_t npad = 0u;

  if (len > 0) {
    if (n > 0) {
      while (digit > n) {
        digit /= 10;
        --total_digits;
      }
    } else {
      digit = 1;
      total_digits = 1;
    }
    if (total_digits > len) {
      for (uint8_t i = 0; i < len; i++)
        *s++ = '-';
    } else {
      if (total_digits < len && pad_leading) {
        npad = len - total_digits;
        for (uint8_t i = 0; i < npad; i++)
          *s++ = '0';
      }
      do {
        *s++ = '0' + (n - n % digit) / digit % 10;
      } while (digit /= 10);
    }
  }
  *s = '\0';
  return s;
}
