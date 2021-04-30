#ifndef RTC_TIME_HPP
#define RTC_TIME_HPP
#include <stdbool.h>
#include <stdint.h>

#define RTC_DAYS_IN_JAN (31u)
#define RTC_DAYS_IN_FEB (28u)
#define RTC_DAYS_IN_MAR (31u)
#define RTC_DAYS_IN_APR (30u)
#define RTC_DAYS_IN_MAY (31u)
#define RTC_DAYS_IN_JUN (30u)
#define RTC_DAYS_IN_JUL (31u)
#define RTC_DAYS_IN_AUG (31u)
#define RTC_DAYS_IN_SEP (30u)
#define RTC_DAYS_IN_OCT (31u)
#define RTC_DAYS_IN_NOV (30u)
#define RTC_DAYS_IN_DEC (31u)

// #define SNVS_HPSR_PI_MASK (0x2u)
#define IS_LEAP_YEAR(year)                                                     \
  (((((year) % 400u) == 0u) ||                                                 \
    ((((year) % 4u) == 0u) && (((year) % 100u) != 0u)))                        \
       ? true                                                                  \
       : false)
#define YEAR_DAYS(year) ((IS_LEAP_YEAR(year) ? 366u : 365u))

enum rtc_months {
  rtc_january = 1u,
  rtc_february,
  rtc_march,
  rtc_april,
  rtc_may,
  rtc_june,
  rtc_july,
  rtc_august,
  rtc_september,
  rtc_october,
  rtc_november,
  rtc_december
};

const uint8_t days_in_months[12u] = {
    RTC_DAYS_IN_JAN, RTC_DAYS_IN_FEB, RTC_DAYS_IN_MAR, RTC_DAYS_IN_APR,
    RTC_DAYS_IN_MAY, RTC_DAYS_IN_JUN, RTC_DAYS_IN_JUL, RTC_DAYS_IN_AUG,
    RTC_DAYS_IN_SEP, RTC_DAYS_IN_OCT, RTC_DAYS_IN_NOV, RTC_DAYS_IN_DEC,
};

const uint8_t leading_days[12] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};

enum time_format { format_12, format_24 };

class rtc_time {
public:
  rtc_time();
  void one_second_tick();
  inline uint8_t get_seconds() { return seconds; }
  inline uint8_t get_minutes() { return minutes; }
  inline uint8_t get_hours() { return hours; }
  inline uint8_t get_day_of_week() { return day_of_week; }
  inline uint8_t get_day_of_month() { return day_of_month; }
  inline uint8_t get_day_of_year() { return day_of_year; }
  inline uint8_t get_month() { return month; }
  inline uint8_t get_year() { return year; }
  inline uint32_t get_epoch() { return epoch; }
  inline uint32_t get_uptime() { return uptime; }
  inline bool is_tick() { return tick; }
  inline void clear_tick() { tick = false; }
  inline bool is_leap_year() { return leap_year; }
  inline bool is_PM() { return PM; }
  void create_date_time_string(char *str, uint8_t strlen, time_format format);

private:
  uint8_t seconds;
  uint8_t minutes;
  uint8_t hours;
  uint8_t day_of_week;
  uint8_t day_of_month;
  uint16_t day_of_year;
  uint8_t month;
  uint16_t year;
  bool leap_year;
  bool PM;
  uint32_t epoch;
  uint32_t uptime;
  bool tick;
  void read_HPRTC();
  void epoch_to_time();
  void calculate_day_of_week();
};

#endif