static int JsiNumberBase(const char *str, int *base, int *sign)
{
    int i = 0;

    *base = 10;

    while (isspace(UCHAR(str[i]))) {
        i++;
    }

    if (str[i] == '-') {
        *sign = -1;
        i++;
    }
    else {
        if (str[i] == '+') {
            i++;
        }
        *sign = 1;
    }

    if (str[i] != '0') {

        return 0;
    }


    switch (str[i + 1]) {
        case 'x': case 'X': *base = 16; break;
        case 'o': case 'O': *base = 8; break;
        case 'b': case 'B': *base = 2; break;
        default: return 0;
    }
    i += 2;

    if (str[i] != '-' && str[i] != '+' && !isspace(UCHAR(str[i]))) {

        return i;
    }

    return 10;
}
