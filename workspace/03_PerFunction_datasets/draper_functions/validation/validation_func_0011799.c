degeneracy_integer_scores(void)
{
  char *msg = "degeneracy_integer_scores unit test failed";
  ESL_ALPHABET *a;
  ESL_DSQ       x;
  float         p[]  = {0.4, 0.1, 0.1, 0.4};
  int           sc[] = { -1,  -6,   6,   1};
  int           val;

  a     = esl_alphabet_Create(eslDNA);

  x     = esl_abc_DigitizeSymbol(a, 'N');
  val   = esl_abc_IAvgScore(a, x, sc);

  if (val != 0) esl_fatal(msg);

  x     = esl_abc_DigitizeSymbol(a, 'M');
  val   = esl_abc_IExpectScore(a, x, sc, p);

  if (val != -2) esl_fatal(msg);

  esl_alphabet_Destroy(a);
  return eslOK;
}
