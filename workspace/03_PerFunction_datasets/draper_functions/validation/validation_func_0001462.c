visibilityUnobscured(void)
{
  visible(MSTrue);
  MSNodeItem *hp=childListHead();
  MSNodeItem *np=hp;
  MSWidget   *wid;
  while((np=np->next())!=hp)
   {
     wid=(MSWidget *)np->data();
     visibilityUnobscuredNotify(wid);
   }
}
