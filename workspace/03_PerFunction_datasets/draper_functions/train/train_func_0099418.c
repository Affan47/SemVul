loop_giv_reduce_benefit (loop, bl, v, test_reg)
     struct loop *loop ATTRIBUTE_UNUSED;
     struct iv_class *bl;
     struct induction *v;
     rtx test_reg;
{
  int add_cost;
  int benefit;

  benefit = v->benefit;
  PUT_MODE (test_reg, v->mode);
  add_cost = iv_add_mult_cost (bl->biv->add_val, v->mult_val,
			       test_reg, test_reg);


  if (! v->replaceable && ! bl->eliminable
      && REG_USERVAR_P (v->dest_reg))
    benefit -= copy_cost;


  benefit -= add_cost * bl->biv_count;


#ifdef AUTO_INC_DEC


  if (v->giv_type == DEST_ADDR


      && benefit > 0
      && GET_CODE (v->mult_val) == CONST_INT)
    {
      int size = GET_MODE_SIZE (GET_MODE (v->mem));

      if (HAVE_POST_INCREMENT
	  && INTVAL (v->mult_val) == size)
	benefit += add_cost * bl->biv_count;
      else if (HAVE_PRE_INCREMENT
	       && INTVAL (v->mult_val) == size)
	benefit += add_cost * bl->biv_count;
      else if (HAVE_POST_DECREMENT
	       && -INTVAL (v->mult_val) == size)
	benefit += add_cost * bl->biv_count;
      else if (HAVE_PRE_DECREMENT
	       && -INTVAL (v->mult_val) == size)
	benefit += add_cost * bl->biv_count;
    }
#endif

  return benefit;
}
