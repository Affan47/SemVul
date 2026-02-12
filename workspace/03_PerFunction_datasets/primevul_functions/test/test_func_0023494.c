static int cmp_decimal(void *cmp_arg, my_decimal *a, my_decimal *b)
{


  a->fix_buffer_pointer();
  b->fix_buffer_pointer();
  return my_decimal_cmp(a, b);
}
