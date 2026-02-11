TabularCline(const char *row, int columns)


{
    char *s, *x;
    int i, n, m;
    char *cline = NULL;

    cline = (char *) calloc((columns + 2) , sizeof(char));

    if (row == NULL)
        return cline;


    n = TabularHline(row);

    for (i = 0; i <= columns; i++)
        cline[i] = n;

    if (n)
        return cline;

    s = (char *) row;
    x = (char *) row + strlen(row);
    while (s < x) {
        s = strstr(s, "\\cline{");

        if (s == NULL)
            return cline;

        s += 7;

        while (*s && (*s == ' ' || *s == '\n'))
            s++;

        if (*s <= '0' || *s >= '9')
            return cline;
        n = atoi(s);

        while (*s && *s != '-')
            s++;
        s++;

        while (*s && (*s == ' ' || *s == '\n'))
            s++;

        if (*s <= '0' || *s >= '9')
            return cline;
        m = atoi(s);

        for (i = n; i <= m; i++) {
            if (i <= columns && i >= 1)
                cline[i] = 1;
        }
        while (*s && *s != '}')
            s++;
    }

    return cline;
}
