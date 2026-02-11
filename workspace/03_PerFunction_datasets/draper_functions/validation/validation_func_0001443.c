freemystack(head)
mystack *head;
{
  mystack *scan,*old;

  old=NULL;
  for(scan=head;scan;scan=scan->NEXT)
  {
    if(old)
      mbkfree(old);
    old=scan;
  }
  if(old)
    mbkfree(old);
}
