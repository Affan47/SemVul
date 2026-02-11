prep_comb_udptab(struct udp_t *udpp)
{
 register struct utline_t *utlp;
 word32 nstates;
 int32 blen, bytsiz;
 word32 ndx;
 char out_ch;


 __cur_ueipnum = NO_VAL;
 __cur_utabsel = NO_VAL;

 nstates = udpp->numstates;

 if (udpp->u_wide) blen = comb2tabsiz[nstates];
 else blen = combtabsiz[nstates];


 bytsiz = WRDBYTES*wlen_(blen);


 __cur_utab = (word32 *) __my_malloc(bytsiz);

 init_utab(__cur_utab, blen);
 __cur_udp = udpp;

 for (utlp = udpp->utlines; utlp != NULL; utlp = utlp->utlnxt)
  {

   if (utlp->uledinum != NO_VAL) continue;

   __sfnam_ind = utlp->utlfnam_ind;
   __slin_cnt = utlp->utlin_cnt;


   if (utlp->ulhas_wcard) bld_wcardtab(utlp->tline, nstates, nstates + 1);


   ndx = bld_uinitndx(utlp->tline, nstates, -1);


   out_ch = utlp->tline[udpp->numstates];


   if (out_ch == '-') __cur_unochange = TRUE;
   else
    {

     __cur_unochange = FALSE;

     __cur_uoval = (word32) ((out_ch == '0') ? 0 : ((out_ch == '1') ? 1 : 2));
    }

   if (utlp->ulhas_wcard) xpnd_1wcard(0, ndx);


   else setchk_uval(ndx);
  }

 chg_unfilled_tox(__cur_utab, blen);
}
