test_box_conversion(void)
{
  printf("\nconversion to box %s\n",num_incomplete?"":"(* expected)");
  LOOP {
    size_t dim = 6;
    int i;
    oct_t *o,*o2,*o3;
    ap_interval_t **b,**b2;
    o = random_oct(dim,.1);
    b = oct_to_box(mo,o); FLAG(mo);
    o2 = oct_of_box(mo,0,dim,b); FLAG(mo);
    b2 = oct_to_box(mo,o2); FLAG(mo);
    o3 = oct_of_box(mo,0,dim,b2); FLAG(mo);
    RESULT(check(o)); check(o2);
    if (oct_is_nleq(mo,o,o2) || oct_is_nleq(mo,o2,o3)) {
      ERROR("not included in");
      print_oct("o",o);
      print_oct("o2",o2);
      print_oct("o3",o3);
    }
    if (oct_is_eq(mo,o2,o3)) RESULT('*');
    if (flag==exact && oct_is_neq(mo,o2,o3)) ERROR("exact flag");
    ap_interval_array_free(b,dim);
    ap_interval_array_free(b2,dim);
    oct_free(mo,o); oct_free(mo,o2); oct_free(mo,o3);
  } ENDLOOP;
}
