validate_insn_alternatives (d)
     struct data *d;
{
  int n = 0, start;


  for (start = 0; start < d->n_operands; start++)
    if (d->operand[start].n_alternatives > 0)
      {
	if (n == 0)
	  n = d->operand[start].n_alternatives;
	else if (n != d->operand[start].n_alternatives)
	  {
	    message_with_line (d->lineno,
			       "wrong number of alternatives in operand %d",
			       start);
	    have_error = 1;
	  }
      }


  d->n_alternatives = n;
}
