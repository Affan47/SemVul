aarch64_simd_expand_builtin (int fcode, tree exp, rtx target)
{
  aarch64_simd_builtin_datum *d =
		&aarch64_simd_builtin_data[fcode - (AARCH64_SIMD_BUILTIN_BASE + 1)];
  enum insn_code icode = d->code;
  builtin_simd_arg args[SIMD_MAX_BUILTIN_ARGS];
  int num_args = insn_data[d->code].n_operands;
  int is_void = 0;
  int k;

  is_void = !!(d->qualifiers[0] & qualifier_void);

  num_args += is_void;

  for (k = 1; k < num_args; k++)
    {


      int qualifiers_k = k;
      int operands_k = k - is_void;
      int expr_args_k = k - 1;

      if (d->qualifiers[qualifiers_k] & qualifier_immediate)
	args[k] = SIMD_ARG_CONSTANT;
      else if (d->qualifiers[qualifiers_k] & qualifier_maybe_immediate)
	{
	  rtx arg
	    = expand_normal (CALL_EXPR_ARG (exp,
					    (expr_args_k)));

	  bool op_const_int_p =
	    (CONST_INT_P (arg)
	     && (*insn_data[icode].operand[operands_k].predicate)
		(arg, insn_data[icode].operand[operands_k].mode));
	  args[k] = op_const_int_p ? SIMD_ARG_CONSTANT : SIMD_ARG_COPY_TO_REG;
	}
      else
	args[k] = SIMD_ARG_COPY_TO_REG;

    }
  args[k] = SIMD_ARG_STOP;


  return aarch64_simd_expand_args
	  (target, icode, !is_void, exp,
	   args[1],
	   args[2],
	   args[3],
	   args[4],
	   SIMD_ARG_STOP);
}
