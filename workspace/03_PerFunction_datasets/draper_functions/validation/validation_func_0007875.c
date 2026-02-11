MR_predContextPresent(Predicate *p,int *allHaveContext,int *noneHaveContext)
#else
void MR_predContextPresent(p,allHaveContext,noneHaveContext)
  Predicate     *p;
  int           *allHaveContext;
  int           *noneHaveContext;
#endif
{
  if (p == NULL) return;
  MR_predContextPresent(p->right,allHaveContext,noneHaveContext);
  if (p->expr != PRED_AND_LIST &&
      p->expr != PRED_OR_LIST) {
    if (set_nil(p->scontext[1]) == 0 ||
            (p->tcontext != NULL)) {
      *noneHaveContext=0;
    } else {
      *allHaveContext=0;
    };
  };
  MR_predContextPresent(p->down,allHaveContext,noneHaveContext);
}
