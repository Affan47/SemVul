Cudd_ApaSetToLiteral(
  int  digits,
  DdApaNumber  number,
  DdApaDigit  literal)
{
    int i;

    for (i = 0; i < digits - 1; i++)
	number[i] = 0;
    number[digits - 1] = literal;

}
