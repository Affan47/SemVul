bld_net_tchkterms(struct net_t *np, struct itree_t *itp, int32 ndx)
{
 register int32 cnt;
 register struct net_pin_t *npp;
 register struct h_t *hp2;
 register struct hrec_t *hrp2;
 struct tchk_t *tcp;
 struct tchg_t *tchgp;

 __push_itstk(itp);

 for (cnt = 0, npp = np->nlds; npp != NULL; npp = npp->npnxt)
  {
   if (npp->npntyp != NP_TCHG) continue;


   if (npp->chgsubtyp != NPCHG_TCSTART) continue;


   tchgp = npp->elnpp.etchgp;
   tcp = tchgp->chgu.chgtcp;
   if (termexpr_matches(tcp->startxp, np, ndx))
    {
     if (cnt >= __ithtsiz) __grow_htab(cnt - __ithtsiz + 1);
     hp2 = &(__ithtab[cnt]);
     hp2->hin_itp = itp;

     hrp2 = &(__ithrectab[cnt++]);
     __init_hrec(hrp2);

     hrp2->in_iter = TRUE;
     hrp2->htyp = vpiTchkTerm;
     hrp2->htyp2 = vpiTchkRefTerm;
     hrp2->hu.htcp = tcp;

     hp2->hrec = hrp2;
    }
   if (termexpr_matches(tcp->chkxp, np, ndx))
    {
     if (cnt >= __ithtsiz) __grow_htab(cnt - __ithtsiz + 1);
     hp2 = &(__ithtab[cnt]);
     hp2->hin_itp = itp;

     hrp2 = &(__ithrectab[cnt++]);
     __init_hrec(hrp2);
     hrp2->in_iter = TRUE;
     hrp2->htyp = vpiTchkTerm;
     hrp2->htyp2 = vpiTchkDataTerm;
     hrp2->hu.htcp = tcp;

     hp2->hrec = hrp2;
    }
  }
 __pop_itstk();
 return(cnt);
}
