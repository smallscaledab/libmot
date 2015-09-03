#ifndef COMMON_H
#define COMMON_H

#include <vector>

using namespace std;

namespace mot
{

	vector<unsigned char> timepoint_to_encoded_utc(int timepoint);

	int timepoint_to_mjd(int timepoint);
}

#endif // COMMON_H
