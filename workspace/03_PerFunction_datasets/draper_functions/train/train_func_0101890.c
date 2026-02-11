push_range_stack (tree range_end, struct obstack * braced_init_obstack)
{
  struct constructor_range_stack *p;

  p = (struct constructor_range_stack *)
    obstack_alloc (braced_init_obstack,
		   sizeof (struct constructor_range_stack));
  p->prev = constructor_range_stack;
  p->next = 0;
  p->fields = constructor_fields;
  p->range_start = constructor_index;
  p->index = constructor_index;
  p->stack = constructor_stack;
  p->range_end = range_end;
  if (constructor_range_stack)
    constructor_range_stack->next = p;
  constructor_range_stack = p;
}
