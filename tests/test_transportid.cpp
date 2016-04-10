#include <vector>
#include <iostream>
#include <mot.h>

using namespace mot;
using namespace std;

int main()
{
    SequentialTransportIdGenerator id(8000);
    if(id.Next() != 8000) return 1;
    if(id.Next() != 8001) return 1;
    if(id.Next() != 8002) return 1;
    if(id.Next() != 8003) return 1;
    if(id.Next() != 8004) return 1;
    if(id.Next() != 8005) return 1;
}
