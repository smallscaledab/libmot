#ifndef CHARSETS_H_
#define CHARSETS_H_

#include "mot.h"

namespace mot
{
	typedef int Charset;

    namespace Charsets
    {
        namespace EBU
        {
            const Charset Latin = 0;
            const Charset Latin_Common_Core = 1;
            const Charset Latin_Core = 2;
        }
        namespace ISO
        {
            const Charset Latin2 = 3;
            const Charset Latin1 = 4;
            const Charset IEC_10646 = 15;
        }
    }
}

#endif /* CHARSETS_H_ */
