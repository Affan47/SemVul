ParseTMGGame(const char *sz, int *piGame, int *pn0, int *pn1, int *pfCrawford, int *post_crawford, const int nLength)
{
    int i = sscanf(sz, "Game %d: %d-%d", piGame, pn0, pn1) == 3;

    if (!i)
        return FALSE;

    if (nLength) {
        if (!*post_crawford)
            *post_crawford = *pfCrawford = (*pn0 == (nLength - 1))
                || (*pn1 == (nLength - 1));
        else
            *pfCrawford = FALSE;
    }

    return TRUE;
}
