do_acc_child_topmod(char *rtnnam, handle child)
{
 struct h_t *hp2;
 vpiHandle ihref, nxth;
 struct acciter_t *aip;

 if (child == NULL)
  {
   __acc_vpi_erroff = TRUE;
   ihref = vpi_iterate(vpiModule, NULL);
   if (__my_vpi_chk_error())
    {
     __acc_err(1983, "%s error finding first top level instance", rtnnam);
     return(NULL);
    }
   if (ihref == NULL) return(NULL);

   aip = alloc_aiter();

   aip->aiter = (struct h_t *) ihref;
   __last_aiter = aip;

   aip->aiternxt = __aiter_tab[vpiModule];
   __aiter_tab[vpiModule] = aip;
   aip->aiterprev = NULL;
   nxth = vpi_scan((vpiHandle) aip->aiter);

   if (nxth == NULL) __acc_terr(__FILE__, __LINE__);

   return((handle) nxth);
  }

 hp2 = (struct h_t *) child;
 if (!validate_acc_handle(rtnnam, hp2)) return(NULL);
 if (hp2->hrec->htyp != vpiModule)
  {
   wrong_nxtobj_error(rtnnam, hp2->hrec->htyp, accModule);
   return(NULL);
  }

 if ((aip = find_aiter_rec(__aiter_tab[vpiModule], hp2)) == NULL)
  {
   __acc_err(1984,
    "%s last accModule object not returned by previous %s call",
    rtnnam, rtnnam);
   return(NULL);
  }
 nxth = vpi_scan((vpiHandle) aip->aiter);
 if (nxth == NULL) { linkout_aiter(aip, vpiModule, FALSE); return(NULL); }
 return((handle) nxth);
}
