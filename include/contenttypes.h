#ifndef CONTENTTYPES_H_
#define CONTENTTYPES_H_

#include "mot.h"

namespace mot
{
	namespace ContentTypes
	{
		// general data
		namespace General
		{
			const ContentType Object_Transfer = {0, 0};
			const ContentType MIME_HTTP = {0, 1};
		}

		// text
		namespace Text
		{
			const ContentType ASCII = {1, 0};
			const ContentType ISO = {1, 1};
			const ContentType HTML = {1, 2};
		}

		// image
		namespace Image
		{
			const ContentType GIF = {2, 0};
			const ContentType JFIF = {2, 1};
			const ContentType BMP = {2, 2};
			const ContentType PNG = {2, 3};
		}

		// audio
		namespace Audio
		{
			const ContentType MPEG1_L1 = {3, 0};
			const ContentType MPEG1_L2 = {3, 1};
			const ContentType MPEG1_L3 = {3, 2};
			const ContentType MPEG2_L1 = {3, 3};
			const ContentType MPEG2_L2 = {3, 4};
			const ContentType MPEG2_L3 = {3, 5};
			const ContentType PCM = {3, 6};
			const ContentType AIFF = {3, 7};
			const ContentType ATRAC = {3, 8};
			const ContentType ATRAC2 = {3, 9};
			const ContentType MPEG4 = {3, 10};
		}

		// video
		namespace Video
		{
			const ContentType MPEG1 = {4, 0};
			const ContentType MPEG2 = {4, 1};
			const ContentType MPEG4 = {4, 2};
			const ContentType H263 = {4, 3};
		}
    }
}

#endif /* CONTENTTYPES_H_ */
