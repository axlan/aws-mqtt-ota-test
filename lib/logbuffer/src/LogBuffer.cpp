#include "LogBuffer.h"
#include <string.h>
#include <stdio.h>

static const int BUFF_SIZE = 1024;
static char BUFFER[BUFF_SIZE];

static int head;
static int tail;

void LogBuffer::Clear() {
    head = 0;
    tail = 0;
}

void LogBuffer::Write(int val)
{
   char msg[16];
   sprintf(msg, "%d", val);
   Write(msg);
}

void LogBuffer::Write(const char * msg)
{
    int len = strlen(msg) + 1;
    if (head + len > BUFF_SIZE) {
        strcpy(BUFFER, "OVERFLOW");
        head = 9;
        return;
    }

    memcpy(&BUFFER[head], msg, len);
    head += len;
}

const char * LogBuffer::Read()
{
    if (IsEmpty()) {
        return NULL;
    }

    const char * ptr = &BUFFER[tail];
    int len = strlen(ptr) + 1;
    tail += len;
    return ptr;
}

bool LogBuffer::IsEmpty()
{
    return head == tail;
}
