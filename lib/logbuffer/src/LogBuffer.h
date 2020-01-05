#pragma once

class LogBuffer
{
public:
    static void Clear();
    static void Write(int val);
    static void Write(const char * msg);
    static const char * Read();
    static bool IsEmpty();
};
