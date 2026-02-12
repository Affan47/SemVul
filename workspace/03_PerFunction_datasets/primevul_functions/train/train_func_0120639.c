int UZ_EXP UzpPassword (pG, rcnt, pwbuf, size, zfn, efn)
    zvoid *pG;
    int *rcnt;
    char *pwbuf;
    int size;
    ZCONST char *zfn;
    ZCONST char *efn;
{
#if CRYPT
    int r = IZ_PW_ENTERED;
    char *m;
    char *prompt;

#ifndef REENTRANT

    (void)pG;
#endif

    if (*rcnt == 0) {
        *rcnt = 2;
        if ((prompt = (char *)malloc(2*FILNAMSIZ + 15)) != (char *)NULL) {
            sprintf(prompt, LoadFarString(PasswPrompt),
                    FnFilter1(zfn), FnFilter2(efn));
            m = prompt;
        } else
            m = (char *)LoadFarString(PasswPrompt2);
    } else {
        (*rcnt)--;
        prompt = NULL;
        m = (char *)LoadFarString(PasswRetry);
    }

    m = getp(__G__ m, pwbuf, size);
    if (prompt != (char *)NULL) {
        free(prompt);
    }
    if (m == (char *)NULL) {
        r = IZ_PW_ERROR;
    }
    else if (*pwbuf == '\0') {
        r = IZ_PW_CANCELALL;
    }
    return r;

#else

    (void)pG; (void)rcnt; (void)pwbuf; (void)size; (void)zfn; (void)efn;

    return IZ_PW_ERROR;
#endif

}
