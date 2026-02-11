ngram_make_lookup_tree(NGRAM_INFO *ndata)
{
  int i;
  int *windex;
  char **wnameindex;

  windex = (int *)mymalloc(sizeof(int)*ndata->max_word_num);
  for (i=0;i<ndata->max_word_num;i++) {
    windex[i] = i;
  }
  wnameindex = (char **)mymalloc(sizeof(char *)*ndata->max_word_num);
  for (i=0;i<ndata->max_word_num;i++) {
    wnameindex[i] = ndata->wname[i];
  }

  ndata->root = make_ptree(wnameindex, windex, ndata->max_word_num, 0, &(ndata->mroot));

  free(windex);
  free(wnameindex);
}
