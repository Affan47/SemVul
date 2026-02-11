gnubase(gbases **p, gbases **garbage, long endsite)
{


  if (*garbage != NULL) {
    *p = *garbage;
    *garbage = (*garbage)->next;
  } else {
    *p = (gbases *)Malloc(sizeof(gbases));
    (*p)->discbase = (discbaseptr)Malloc(endsite*sizeof(unsigned char));
  }
  (*p)->next = NULL;
}
