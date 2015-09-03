#include "common.h"
#include "util.h"

#include <bitset>
#include <math.h>

namespace mot
{
    int timepoint_to_mjd(int timepoint)
    {
        time_t t = timepoint / 1000;

        struct tm *tm;
        tm = gmtime(&t);

        int day = tm->tm_yday;
        int month = tm->tm_mon;
        int year = tm->tm_year + 1900;

        int yearp = 0;
        int monthp = 0;
        if(month == 1 || month == 2)
        {
            yearp = year - 1;
            monthp = month + 12;
        } else {
            yearp = year;
            monthp = month;
        }

        int A, B = 0;
        if  ((year < 1582) ||
            (year == 1582 && month < 10) ||
            (year == 1582 && month == 10 && day < 15))
        {
            B = 0;
        } else {
            A = trunc(yearp / 100.0);
            B = 2 - A + trunc(A / 4.0);
        }

        int C = 0;
        if(yearp < 0)
        {
            C = trunc((365.25 * yearp) - 0.75);
        } else {
            C = trunc(365.25 * yearp);
        }

        int D = trunc(30.6001 * (monthp + 1));

        int jd = B + C + D + day + 1720994.5;
        int mjd = jd - 2400000.5;

        return mjd;
    }

    vector<unsigned char> timepoint_to_encoded_utc(int timepoint)
    {
           if(timepoint == 0) // NOW
           {
                   bitset<32> bits(0);
                   return bits_to_bytes(bits);
           }

           if(timepoint / (60000))
           {
                   int mjd = timepoint_to_mjd(timepoint);
                   bitset<48> bits(1  + // validity flag (1)
                                              (mjd << 1) + // mjd (16)
                                              (0) + // rfu (2)
                                              (1 << 19) + // UTC flag
                                              (timepoint << 20)); // timepoint (27)
                   return bits_to_bytes(bits);
           }
           else
           {
                   int mjd = timepoint_to_mjd(timepoint);
                   bitset<32> bits(1  + // validity flag (1)
                                              (mjd << 1) + // mjd (16)
                                              (0) + // rfu (2)
                                              (1 << 19) + // UTC flag
                                              ((timepoint / 60000) << 20)); // timepoint (11)
                   return bits_to_bytes(bits);
           }
    }
}
