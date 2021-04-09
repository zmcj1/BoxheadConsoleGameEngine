#include "Utils.h"

namespace MinConsoleNative
{
    bool is_str_utf8(const char* str)
    {
        unsigned int nBytes = 0;
        unsigned char chr = *str;
        bool bAllAscii = true;

        for (unsigned int i = 0; str[i] != '\0'; ++i)
        {
            chr = *(str + i);
            if (nBytes == 0 && (chr & 0x80) != 0)
            {
                bAllAscii = false;
            }

            if (nBytes == 0)
            {
                if (chr >= 0x80)
                {
                    if (chr >= 0xFC && chr <= 0xFD)
                    {
                        nBytes = 6;
                    }
                    else if (chr >= 0xF8)
                    {
                        nBytes = 5;
                    }
                    else if (chr >= 0xF0)
                    {
                        nBytes = 4;
                    }
                    else if (chr >= 0xE0)
                    {
                        nBytes = 3;
                    }
                    else if (chr >= 0xC0)
                    {
                        nBytes = 2;
                    }
                    else
                    {
                        return false;
                    }

                    nBytes--;
                }
            }
            else
            {
                if ((chr & 0xC0) != 0x80)
                {
                    return false;
                }
                nBytes--;
            }
        }

        if (nBytes != 0)
        {
            return false;
        }

        if (bAllAscii)
        {
            return true;
        }

        return true;
    }
}