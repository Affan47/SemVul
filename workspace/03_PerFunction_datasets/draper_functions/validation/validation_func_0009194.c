chg_unfilled_tox(word32 *taddr, int32 blen)
{
 register word32 tmp;
 register int32 wi, bi;
 int32 wlen, ubits;

 wlen = wlen_(blen);
 for (wi = 0; wi < wlen - 1; wi++)
  {

   if ((tmp = taddr[wi]) == ALL1W) continue;


   for (bi = 0; bi < WBITS; bi += 2)
    {
     if (((tmp >> bi) & 0x3L) == 2L)
      tmp |= (3L << bi);
    }
   taddr[wi] = tmp;
  }

 if ((tmp = taddr[wlen - 1]) == ALL1W) return;


 if ((ubits = ubits_(blen)) == 0) ubits = WBITS;
 for (bi = 0; bi < ubits; bi += 2)
  {
   if (((tmp >> bi) & 0x3L) == 2L) tmp |= (3L << bi);
  }
 taddr[wlen - 1] = tmp;
}
