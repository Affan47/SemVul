free_all_protx (long nonodes, pointarray treenode)
{

  long i, j, k;
  node *p;


  for (i = 0; i < spp; i++) {
    for (j = 0; j < endsite; j++)
      free(treenode[i]->protx[j]);
    free(treenode[i]->protx);
  }


  for (i = spp; i < nonodes; i++) {
    if (treenode[i] != NULL) {
      p = treenode[i];
      do {
        for (k = 0; k < endsite; k++)
          free(p->protx[k]);
        free(p->protx);
        p = p->next;
      } while (p != treenode[i]);
    }
  }
}
