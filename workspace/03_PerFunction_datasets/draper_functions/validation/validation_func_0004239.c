PrependRlistAlien(struct Rlist **start,void *item)


{ struct Rlist *rp;

ThreadLock(cft_lock);

if ((rp = (struct Rlist *)malloc(sizeof(struct Rlist))) == NULL)
   {
   CfOut(cf_error,"malloc","Unable to allocate Rlist");
   FatalError("");
   }

rp->next = *start;
*start = rp;
ThreadUnlock(cft_lock);

rp->item = item;
rp->type = CF_SCALAR;
return rp;
}
