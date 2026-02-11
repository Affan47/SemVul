bitwisechk(A a,A w,I i)
{
  I anonbool=0, wnonbool=0, tot=0;
  if(dbg_hold)R 0;
  DO(a->n,if((unsigned long)(a->p[i])&(unsigned long)(~0x01))++anonbool;);
  if(w)DO(w->n,if((unsigned long)(w->p[i])&(unsigned long)(~0x01))++wnonbool;);
  if(anonbool||wnonbool)
  {
    C **primnames=get_primlist(APL,0);
    tot=anonbool+wnonbool;
    if(anonbool&&wnonbool)
    {
      DH("\343%sWarning: found %ld non-boolean%s in both arguments of %s.\n",
	 dbg_pfx(),tot,(1<tot)?"s":"",primnames[i]);
    }
    else if (anonbool)
    {
      DH("\343%sWarning: found %ld non-boolean%s in%s argument of %s.\n",
	 dbg_pfx(),tot,(1<tot)?"s":"",(w)?" left":"",primnames[i]);
    }
    else
    {
      DH("\343%sWarning: found %ld non-boolean%s in right argument of %s.\n",
	 dbg_pfx(),tot,(1<tot)?"s":"",primnames[i]);
    }
  }
  FFL;
  R -1;
}
