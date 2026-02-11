strncpy_printable(char* dst, char *src, int n)
{
    int i=0;

    if (dst == NULL)
        return;

    while (i<n-1 && *src) {

        if (*src=='\r') {
            dst[i++]='\\';
            dst[i++]='r';
         } else if (*src=='\n') {
            dst[i++]='\\';
            dst[i++]='n';
         } else if (*src=='\t') {
            dst[i++]='\\';
            dst[i++]='t';
         } else
            dst[i++]=*src;
         src++;
    }

    dst[i]='\0';
}
