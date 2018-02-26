#include "stdafx.h"
#include "Hashing.h"

using namespace std;

namespace hashing
{
    unsigned int GetFileHash_CRC32(const char * FilePath_)
    {
        ifstream f(FilePath_, ios::binary | ios::ate);
        if (!f.is_open())
            return 0;

        
        return 0;
    }
}
