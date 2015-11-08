#include <vector>
#include <iostream>
#include <mot.h>

using namespace mot;
using namespace std;

int main()
{
    SequentialTransportIdGenerator* id = SequentialTransportIdGenerator::getInstance(8000);
    if(id->next() != 8000) return 1;
    if(id->next() != 8001) return 1;
    if(id->next() != 8002) return 1;
    if(id->next() != 8003) return 1;
    if(id->next() != 8004) return 1;
    if(id->next() != 8005) return 1;
}
