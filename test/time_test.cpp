#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;
using namespace std::chrono;

int main ()
{
    seconds s(1442684842);

// split into hours, minutes, seconds, and milliseconds
hours   hh = duration_cast<hours>(s) % 24;
int days = duration_cast<hours>(s).count() / 24;
minutes mm = duration_cast<minutes>(s % chrono::hours(1));
seconds ss = duration_cast<seconds>(s % chrono::minutes(1));
milliseconds msec
           = duration_cast<milliseconds>(s % chrono::seconds(1));

// and print durations and values:
cout << "days: " << days << endl;
cout << "     " << hh.count() << "::"
                                << mm.count() << "::"
                                << ss.count() << "::"
                                << msec.count() << endl;
}
