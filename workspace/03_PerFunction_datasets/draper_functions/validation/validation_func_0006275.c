__free_icptab(void)
{
 register int32 ii;
 int32 pnum;
 struct srcloc_t *iplocs;
 struct inst_t *ip;
 struct mod_t *imdp;


 if (!__inst_mod->msplit && !__inst_mod->mpndsplit)
  {
   for (ii = 0; ii < __inst_mod->minum; ii++)
    {

     iplocs = __inst_mod->iploctab[ii];

     ip = &(__inst_mod->minsts[ii]);
     imdp = ip->imsym->el.emdp;

     if ((pnum = imdp->mpnum) != 0)
      __my_free((char *) iplocs, pnum*sizeof(struct srcloc_t));
    }
   if (__inst_mod->minum != 0)
    {
     __my_free((char *) __inst_mod->iploctab,
      __inst_mod->minum*sizeof(struct srcloc_t **));
    }
  }
 __inst_mod->iploctab = NULL;
}
