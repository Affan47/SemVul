hash_string(const unsigned char *s, int n)
{
    int h = 0;

    while(*s)
        h += (h << 7) + *s++;
    h = (h * SOMEPRIME) % n;
    h = (h >= 0) ? h : h + n;

    return (h % n);
}
