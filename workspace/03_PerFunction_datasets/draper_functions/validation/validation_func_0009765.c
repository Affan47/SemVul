voctplfnd(voccxdef *ctx, objnum verb_in, objnum prep,
              uchar *tplout, int *newstyle)
{
    uchar  *tplptr;
    uchar  *thistpl;
    int     found;
    int     tplcnt;
    uint    tplofs;
    objnum  verb;


    tplofs = objgetap(ctx->voccxmem, verb_in, PRP_TPL2, &verb, FALSE);
    if (tplofs)
    {

        *newstyle = TRUE;
    }
    else
    {

        tplofs = objgetap(ctx->voccxmem, verb_in, PRP_TPL, &verb, FALSE);
        *newstyle = FALSE;
    }


    for (;;)
    {

        if (tplofs)
        {
            size_t siz;


            siz = (*newstyle ? VOCTPL2SIZ : VOCTPLSIZ);


            tplptr  = mcmlck(ctx->voccxmem, verb);
            thistpl = prpvalp(tplptr + tplofs);


            tplcnt = *thistpl++;


            for (found = FALSE ; tplcnt ; thistpl += siz, --tplcnt)
            {
                if (voctplpr(thistpl) == prep)
                {
                    found = TRUE;
                    break;
                }
            }


            mcmunlck(ctx->voccxmem, verb);
            if (found)
            {
                memcpy(tplout, thistpl, siz);
                return(TRUE);
            }
        }


        tplofs = objgetap(ctx->voccxmem, verb_in, PRP_TPL2, &verb, TRUE);
        if (tplofs)
            *newstyle = TRUE;
        else
        {
            tplofs = objgetap(ctx->voccxmem, verb_in, PRP_TPL, &verb, TRUE);
            *newstyle = FALSE;
        }


        if (!tplofs)
            return FALSE;


        verb_in = verb;
    }
}
