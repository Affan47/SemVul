gt_array_rem_span(GtArray *a, unsigned long frompos, unsigned long topos)
{
  unsigned long i, len;
  gt_assert(a && frompos <= topos);
  gt_assert(frompos < a->next_free && topos < a->next_free);

  len = topos - frompos + 1;
  for (i = topos + 1; i < a->next_free; i++) {
    memcpy((char*) a->space + (i-len) * a->size_of_elem,
           (char*) a->space + i * a->size_of_elem,
           a->size_of_elem);
  }

  a->next_free -= len;
}
