__zzip_aligned4(char *p)
{
#define aligned4   __zzip_aligned4
    p += ((long) p) & 1;
    p += ((long) p) & 2;
    return p;
}
