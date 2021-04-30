#include <Arduino.h>
#include "rtc_time.h"
#include "string_utilities.h"

// uint8_t rtc_time::get_seconds() { return seconds; }
// uint8_t rtc_time::get_minutes() { return minutes; }
// uint8_t rtc_time::get_hours() { return hours; }
// uint8_t rtc_time::get_month() { return month; }
// uint8_t rtc_time::get_year() { return year; }
// uint8_t rtc_time::get_day_of_month() { return day_of_month; }
// uint8_t rtc_time::get_day_of_week() { return day_of_week; }
// uint8_t rtc_time::get_day_of_year() { return day_of_year; }
// uint32_t rtc_time::get_epoch() { return epoch; }
// uint32_t rtc_time::get_uptime() { return uptime; }
// bool rtc_time::is_leap_year() { return leap_year; }
// bool rtc_time::is_PM() { return PM; }
// bool rtc_time::is_tick() { return tick; }
// void rtc_time::clear_tick() { tick = false; }

rtc_time::rtc_time() 
{ 
  uptime = 0u;
  tick = false;
  read_HPRTC();
  epoch_to_time();
}

void rtc_time::one_second_tick() {
  seconds++;
  if (seconds > 59u) {
    minutes++;
    seconds = 0u;
    if (minutes > 59u) {
      hours++;
      minutes = 0u;
      if (hours > 23u) {
        day_of_month++;
        hours = 0u;
        day_of_year++;
        day_of_week++;
        // Sun = 0, Sat = 6
        if (day_of_week > 6u) {
          day_of_week = 0u;
        }

        /* Day of month roll over.
         * Check February in leap year, other months in leap year,
         * and months in non-leap years.
         */
        if (((leap_year) && (month == rtc_february) &&
             (day_of_month > (days_in_months[month - 1u] + 1u))) ||
            ((leap_year) && (month != rtc_february) &&
             (day_of_month > days_in_months[month - 1u])) ||
            ((!leap_year) && (day_of_month > days_in_months[month - 1u]))) {
          month++;
          day_of_month = 1u;
          if (month > 12u) {
            year++;
            month = 1u;
            day_of_year = 1u;
            leap_year = IS_LEAP_YEAR(year);
          } /* Month > 12 */
        }   /* Day roll over */
      }     // if(hours > 23u)
      if (hours < 12u) {
        PM = false;
      } else {
        PM = true;
      }
    } // if(minutes > 59u)
  }   // if(seconds > 59u)
  tick = true;
}

void rtc_time::read_HPRTC()
{
  uint64_t readTime1 = 0u;
  uint64_t readTime2 = 0u;
  bool status_ok = false;
  for (uint8_t i = 0u; i < 3u; i++) {
    readTime1 = ((((uint64_t)(SNVS_HPRTCMR & 0x7FFF)) << 32u) | (SNVS_HPRTCLR));
    readTime2 = ((((uint64_t)(SNVS_HPRTCMR & 0x7FFF)) << 32u) | (SNVS_HPRTCLR));
    if (readTime1 == readTime2) {
        epoch = (uint32_t)(readTime1 >> 15u);
        status_ok = true;
        break;
    }
  }
  if(!status_ok) {
    epoch = 0u;
  }
}

void rtc_time::epoch_to_time()
{
  uint32_t time;
  uint32_t my_days = 0u;
  uint8_t month_days = 0u;

  year = 1970u;           // Epoch starts at 1970-01-01 00:00:00

  time = epoch;
  seconds = time % 60u;
  time /= 60u;            // Remainder minutes
  minutes = time % 60u;
  time /= 60u;            // Remainder hours
  hours = time % 24u;
  time /= 24u;            // Remainder days

  while((my_days += YEAR_DAYS(year)) < time) { ++year; }
  leap_year = IS_LEAP_YEAR(year);
  my_days -= leap_year ? 366u : 365u;
  time -= my_days;        // Remainder days in current year
  day_of_year = time + 1;

  for(month = 0u; month < 12u; month++) {
    if(month == 1u) {
      if(leap_year) {
        month_days = 29u;
      } else {
        month_days = 28u;
      }
    } else {
      month_days = days_in_months[month];
    }

    if(time >= month_days) {
      time -= month_days;
    } else {
      break;
    }
  }
  month += 1;
  day_of_month += time + 1;
  calculate_day_of_week();
}

void rtc_time::calculate_day_of_week()
{
  uint16_t y = year;

  if(month < rtc_march) { y -= 1; }
  // Tomohiko Sakamoto’s Algorithm
  day_of_week = ((uint8_t)(
      ((uint16_t)(y + (((y / 4u) - (y / 100u)) + (y / 400u))) +
       (((uint16_t)leading_days[month - 1u]) + ((uint16_t)day_of_month))) % 7u));
}

void rtc_time::create_date_time_string(char *str, uint8_t strlen, time_format format) 
{
  uint8_t output_hour = hours;

  if(format == format_12) {
    if(hours > 12u) {
      output_hour = hours - 12u;
    } else if(hours == 0) {
      output_hour = 12u;
    }
  }
  /*
   * 123456789012345678901234
   * YYYY/mm/dd HH:MM:SS         = 19 characters
   * YYYY/mm/dd HH:MM:SS PM      = 22 characters
   */
  if((strlen > 19u && format == format_24) || (strlen > 22u)) {
    str = uint16_to_str(year, str, 4u, true);
    *str++ = '/';
    str = uint8_to_str(month, str, 2u, true);
    *str++ = '/';
    str = uint8_to_str(day_of_month, str, 2u, true);
    *str++ = ' ';
    str = uint8_to_str(output_hour, str, 2u, true);
    *str++ = ':';
    str = uint8_to_str(minutes, str, 2u, true);
    *str++ = ':';
    str = uint8_to_str(seconds, str, 2u, true);
    if(format == format_12) {
      *str++ = ' ';
      if(PM) {
        str = strcpy(str, " PM");
      } else {
        str = strcpy(str, " AM");
      }
    }
  }
}