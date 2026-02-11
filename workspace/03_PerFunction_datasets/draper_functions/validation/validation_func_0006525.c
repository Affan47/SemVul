wchmm_free(WCHMM_INFO *w)
{
  int i;


#ifdef PASS1_IWCD

#endif


  mybfree2(&(w->malloc_root));
  if (!w->category_tree) {
#ifdef UNIGRAM_FACTORING
    if (w->fscore != NULL) free(w->fscore);
#endif
  }
#ifdef UNIGRAM_FACTORING
  if (w->start2isolate != NULL) free(w->start2isolate);
#endif
#ifdef PASS1_IWCD
  free(w->outstyle);
#endif
  if (w->hmminfo->multipath) {
    free(w->wordbegin);
  } else {
    free(w->wordend_a);
  }
  if (w->category_tree) free(w->start2wid);
  free(w->startnode);
  free(w->wordend);
  free(w->offset);
  free(w->stend);
  free(w->ac);
  free(w->next_a);
  free(w->self_a);
  free(w->state);
#ifdef PASS1_IWCD
  if (w->category_tree) lcdset_remove_with_category_all(w);
#endif
  if (w->wrk.out_from_len != 0) {
    free(w->wrk.out_from);
    free(w->wrk.out_from_next);
    free(w->wrk.out_a);
    free(w->wrk.out_a_next);
    w->wrk.out_from_len = 0;
  }
  free(w);
}
