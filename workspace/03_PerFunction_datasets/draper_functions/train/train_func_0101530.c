cli_getunamb (const char *tok, void **choices, cli_selector_t sel)
{
        void  **wcon = NULL;
        char      *w = NULL;
        unsigned  mn = 0;
        void    *ret = NULL;

        if (!choices || !tok || !*tok)
                return NULL;

        for (wcon = choices; *wcon; wcon++) {
                w = strtail ((char *)sel (*wcon), tok);
                if (!w)

                        continue;
                if (!*w)

                        return *wcon;

                ret = *wcon;
                mn++;
        }

#ifdef FORCE_MATCH_EXACT
        return NULL;
#else
        return (mn == 1) ? ret : NULL;
#endif
}
