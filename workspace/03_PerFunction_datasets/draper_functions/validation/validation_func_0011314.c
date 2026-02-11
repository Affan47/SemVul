addto_MessageLine(MessageFile *mf, const char *str)
{
  MessageFileLine *mptr = mf->contentsOfFile;
  MessageFileLine *nmptr = NULL;

  if (mptr == NULL)
  {
    mptr = MyMalloc(sizeof(MessageFileLine));
    strcpy(mptr->line, str);
    mf->contentsOfFile = mptr;
  }
  else
  {
    while (mptr->next != NULL)
      mptr = mptr->next;
    nmptr = MyMalloc(sizeof(MessageFileLine));
    strcpy(nmptr->line, str);
    mptr->next = nmptr;
  }
}
