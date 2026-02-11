jsonp_dtostr(char *buffer, size_t size, double value)
{
    int ret;
    char *start, *end;
    size_t length;

    ret = snprintf(buffer, size, "%.17g", value);
    if(ret < 0)
        return -1;

    length = (size_t)ret;
    if(length >= size)
        return -1;

#if JSON_HAVE_LOCALECONV
    from_locale(buffer);
#endif


    if(strchr(buffer, '.') == NULL &&
       strchr(buffer, 'e') == NULL)
    {
        if(length + 3 >= size) {

            return -1;
        }
        buffer[length] = '.';
        buffer[length + 1] = '0';
        buffer[length + 2] = '\0';
        length += 2;
    }


    start = strchr(buffer, 'e');
    if(start) {
        start++;
        end = start + 1;

        if(*start == '-')
            start++;

        while(*end == '0')
            end++;

        if(end != start) {
            memmove(start, end, length - (size_t)(end - buffer));
            length -= (size_t)(end - start);
        }
    }

    return (int)length;
}
