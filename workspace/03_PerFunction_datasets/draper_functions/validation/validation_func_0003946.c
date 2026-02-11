process_trpthdst_ev(register struct tev_t *tevp)
{
 register int32 bi;
 register struct net_t *np;
 register byte *sbp;
 struct traux_t *trap;
 word32 nval, av, bv;
 struct rngdwir_t *dwirp;
 struct xstk_t *xsp;


 np = tevp->tu.tenp->tenu.np;
 bi = tevp->tu.tenp->nbi;


 __my_free((char *) tevp->tu.tenp, sizeof(struct tenp_t));
 tevp->tu.tenp = NULL;

 nval = tevp->outv;
 if (__ev_tracing)
  {
   char s1[RECLEN];

   __evtr_resume_msg();
   __tr_msg(
    "-- processing inout path dest. %s driven value update event, value %s\n",
    __to_evtrwnam(__xs, np, bi, bi, tevp->teitp),
     __to_vvnam(s1, (word32) nval));
  }
 dwirp = np->nu.rngdwir;
 dwirp->wschd_pbtevs[np->nwid*tevp->teitp->itinum + bi] = -1;

 trap = np->ntraux;
 __push_itstk(tevp->teitp);

 if (np->n_stren)
  {

   sbp = &(trap->trnva.bp[__inum*np->nwid]);
   if (sbp[bi] == nval) goto done;
   sbp[bi] = nval;
  }
 else
  {
   if (!np->n_isavec)
    {
     ld_scalval_(&av, &bv, trap->trnva.bp);
     if (nval == (av | (bv << 1))) goto done;


     st2_scalval_(trap->trnva.bp, nval);
    }
   else
    {
     push_xstk_(xsp, np->nwid);
     __ld_perinst_val(xsp->ap, xsp->bp, trap->trnva, np->nwid);
     av = rhsbsel_(xsp->ap, bi);
     bv = rhsbsel_(xsp->bp, bi);
     if (nval == (av | (bv << 1))) { __pop_xstk(); goto done; }
     __lhsbsel(xsp->ap, bi, (nval & 1L));
     __lhsbsel(xsp->bp, bi, ((nval >> 1) & 1L));
     __st_perinst_val(trap->trnva, np->nwid, xsp->ap, xsp->bp);
     __pop_xstk();
    }
  }


 __eval_tran_1bit(np, bi);
done:
 __pop_itstk();
}
