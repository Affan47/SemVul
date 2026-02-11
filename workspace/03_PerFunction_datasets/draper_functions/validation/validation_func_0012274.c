protalloctree()
{
  long i, j;
  node *p, *q;

  treenode = (pointarray)Malloc(nonodes*sizeof(node *));
  for (i = 0; i < (spp); i++) {
    treenode[i] = (node *)Malloc(sizeof(node));
    treenode[i]->numsteps = (steptr)Malloc(chars*sizeof(long));
    treenode[i]->siteset = (seqptr)Malloc(chars*sizeof(sitearray));
    treenode[i]->seq = (aas *)Malloc(chars*sizeof(aas));
  }
  for (i = spp; i < (nonodes); i++) {
    q = NULL;
    for (j = 1; j <= 3; j++) {
      p = (node *)Malloc(sizeof(node));
      p->numsteps = (steptr)Malloc(chars*sizeof(long));
      p->siteset = (seqptr)Malloc(chars*sizeof(sitearray));
      p->seq = (aas *)Malloc(chars*sizeof(aas));
      p->next = q;
      q = p;
    }
    p->next->next->next = p;
    treenode[i] = p;
  }
}
