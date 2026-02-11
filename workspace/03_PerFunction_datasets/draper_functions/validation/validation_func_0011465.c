CompleteContextGuards(void)
#else
CompleteContextGuards()
#endif
{
    ListNode *      p;
    Predicate *     pred;

    if (ContextGuardPredicateList == NULL) return;

    for (p=ContextGuardPredicateList->next; p != NULL; p=p->next) {
      pred=(Predicate *)p->elem;
      recomputeContextGuard(pred);
    }
}
