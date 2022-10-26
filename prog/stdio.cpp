#include <Arduino.h>

#if !DISABLE_USBCDC
extern "C" int putchar(int c)
{
    return Serial.write((unsigned char)c)<1?EOF:(unsigned char)c;
}

extern "C" int puts(const char *s)
{
    return Serial.println(s);
}

extern "C" int printf(const char *format, ...)
{
    char buf[PRINTF_BUF];
    va_list ap;
    va_start(ap, format);
    vsnprintf(buf, sizeof(buf), format, ap);
    va_end(ap);
    return Serial.write(buf);
}
#endif
