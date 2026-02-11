travlock (void)
{
  int i;
  for (i=0; i<L->refSize; i++)
    if (L->refArray[i].status == LOCK)
      markobject(&L->refArray[i].o);
}
