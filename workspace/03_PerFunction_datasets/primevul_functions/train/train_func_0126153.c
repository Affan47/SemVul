matchDomainName(const char *h, const char *d, MatchDomainNameFlags flags)
{
    int dl;
    int hl;

    const bool hostIncludesSubdomains = (*h == '.');
    while ('.' == *h)
        ++h;

    hl = strlen(h);

    if (hl == 0)
        return -1;

    dl = strlen(d);


    while (xtolower(h[--hl]) == xtolower(d[--dl])) {
        if (hl == 0 && dl == 0) {


            return 0;
        }

        if (0 == hl) {


            if (1 == dl && '.' == d[0])
                return 0;
            else
                return -1;
        }

        if (0 == dl) {


            if ('.' == d[0]) {
                if (flags & mdnRejectSubsubDomains) {

                    while(--hl >= 0 && h[hl] != '.');
                    if (hl < 0) {


                        return hostIncludesSubdomains ? 1 : 0;
                    } else
                        return 1;
                } else
                    return 0;
            } else
                return 1;
        }
    }


    if ((flags & mdnHonorWildcards) && h[hl] == '*' && h[hl + 1] == '.')
        return 0;


    if ('.' == d[dl])
        return 1;

    if ('.' == h[hl])
        return -1;

    return (xtolower(h[hl]) - xtolower(d[dl]));
}
