esl_randomness_Init(ESL_RANDOMNESS *r, uint32_t seed)
{
  if (seed == 0) seed = choose_arbitrary_seed();
  if (r->type == eslRND_MERSENNE)
    {
      mersenne_seed_table(r, seed);
      mersenne_fill_table(r);
    }
  else
    {
      r->seed = seed;
      r->x    = jenkins_mix3(seed, 87654321, 12345678);
      if (r->x == 0) r->x = 42;
    }
  return eslOK;
}
