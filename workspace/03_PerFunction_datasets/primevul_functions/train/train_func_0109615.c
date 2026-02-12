DU_stripLeadingSpaces(char *s)
{
    int i, j, n;

    if (s == NULL) return;
    n = OFstatic_cast(int, strlen(s));
    if (n == 0) return;
    if (!isspace(TO_UCHAR(s[0]))) return;


    for (i=0; i<n && isspace(TO_UCHAR(s[i])); i++)

        ;
    if (i<n) {

        for (j=i; j<=n; j++) {
            s[j-i] = s[j];
        }
    } else {

        s[0] = '\0';
    }
}
