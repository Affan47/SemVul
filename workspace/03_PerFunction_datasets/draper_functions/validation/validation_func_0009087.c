caml_lessthan(value v1, value v2)
{
  intnat res = compare_val(v1, v2, 0);
  if (compare_stack != compare_stack_init) compare_free_stack();
  return Val_int(res < 0 && res != UNORDERED);
}
