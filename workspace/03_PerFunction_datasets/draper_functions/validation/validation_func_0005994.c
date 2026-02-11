Stage3_apply_bounds (T this, int minpos, int maxpos, bool revertp) {
  int newnpairs;
  List_T p;
  Pair_T newpair, oldpair;

#if 0
  this->pairs = Pairpool_transfer_bounded(NULL,this->pairs,minpos,maxpos);
  this->pairs = List_reverse(this->pairs);
#else
  this->pairs = Pairpool_clip_bounded(this->pairs,minpos,maxpos);
#endif

  if ((newnpairs = List_length(this->pairs)) == 0) {
    if (revertp == false) {
      return NULL;
    }
  } else {
    FREE_OUT(this->pairarray);
    this->npairs = newnpairs;

    newpair = this->pairarray = (struct Pair_T *) MALLOC_OUT(newnpairs*sizeof(struct Pair_T));
    for (p = this->pairs; p != NULL; p = p->rest) {
      oldpair = (Pair_T) p->first;
      memcpy(newpair++,oldpair,sizeof(struct Pair_T));
    }
  }

  return this;
}
