ReverseIntStack(struct intstack_s *stack)
{
  struct intstack_s *old;
  struct intstack_s *new;

  old        = stack->nxt;
  stack->nxt = NULL;
  while (old != NULL)
    {
      new        = old;
      old        = old->nxt;
      new->nxt   = stack->nxt;
      stack->nxt = new;
    }
}
