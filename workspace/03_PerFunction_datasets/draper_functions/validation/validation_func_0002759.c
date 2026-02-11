edfplus_annotation_count(struct annotationblock **list)
{
  int n=0;

  struct annotationblock *annotlist;

  annotlist = *list;

  while(annotlist != NULL)
  {
    annotlist = annotlist->next_annotation;

    n++;
  }

  return(n);
}
