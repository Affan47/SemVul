test_add_lincons(exprmode mode)
{
  printf("\nadd %slincons %s\n",exprname[mode],
	 num_incomplete?"":(mode<=expr_oct)?"(* expected)":"(*,x,. expected)");
  LOOP {
    size_t i, dim = 6, nb = 4;
    oct_t *o, *o1, *o2;
    ap_abstract0_t *p, *p1, *p2;
    ap_lincons0_array_t ar = ap_lincons0_array_make(nb);
    ap_lincons0_array_t arr = ap_lincons0_array_make(nb);
    random_poly_oct(dim, .2, &o, &p);
    if (lrand48()%10>=8) oct_close(pr,o);
    for (i=0;i<nb;i++) {
      ar.p[i] = ap_lincons0_make((lrand48()%100>=80)?AP_CONS_EQ:
				 (lrand48()%100>=80)?AP_CONS_SUP:
				 AP_CONS_SUPEQ,
				 random_linexpr(mode,dim),
				 NULL);
      arr.p[i] = random_from_lincons(ar.p[i]);
    }
    o1 = oct_meet_lincons_array(mo,false,o,&ar); FLAG(mo);
    p1 = ap_abstract0_meet_lincons_array(mp,false,p,&arr); FLAG(mp);
    p2 = poly_of_oct(o1);
    o2 = oct_of_poly(p1);
    check(o); RESULT(check(o1));
    if (!ap_abstract0_is_leq(mp,p1,p2)) {
      ERROR("not included in");
      ap_lincons0_array_fprint(stderr,&ar,NULL);
      print_poly("p",p); print_poly("p1",p1); print_poly("p2",p2);
      print_oct("o",o); print_oct("o1",o1); print_oct("o2",o2);
    }
    if (ap_abstract0_is_eq(mp,p1,p2)) RESULT('*');
    else if (oct_is_eq(mo,o1,o2)) RESULT('x');
    if (flag>=best && !ap_abstract0_is_eq(mp,p1,p2)) ERROR("best flag");
    if (flag==exact && oct_is_neq(mo,o1,o2)) ERROR("exact flag");
    oct_free(mo,o); oct_free(mo,o1); oct_free(mo,o2);
    ap_abstract0_free(mp,p); ap_abstract0_free(mp,p1); ap_abstract0_free(mp,p2);
    ap_lincons0_array_clear(&ar); ap_lincons0_array_clear(&arr);
   } ENDLOOP;
}
