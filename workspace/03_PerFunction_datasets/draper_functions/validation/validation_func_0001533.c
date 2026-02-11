append(char* buf, int x)
{
    char* l = buf;
    char* r = buf;

    if (x < 0) {
        *r++ = '-';
        x = -x;
    }

    do {
        *r++ = '0' + x % 10;
        x /= 10;
    } while (x);

    char* e = r--;

    while (l < r) {
        const char t = *l;
        *l++ = *r;
        *r-- = t;
    }

    *e = '\0';

    return e;
}
