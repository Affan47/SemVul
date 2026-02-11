check_64(void)
{
  mpfr_t x,y,z;

  mpfr_inits2 (64, x, y, z, (mpfr_ptr) 0);

  mpfr_set_str_binary(x, "1.00100100110110101001010010101111000001011100100101010000000000E54");
  mpfr_set_str_binary(y, "1.00000000000000000000000000000000000000000000000000000000000000E584");
  test_div(z, x, y, MPFR_RNDU);
  if (mpfr_cmp_str (z, "0.1001001001101101010010100101011110000010111001001010100000000000E-529", 2, MPFR_RNDN))
    {
      printf("Error for tdiv for MPFR_RNDU and p=64\nx=");
      mpfr_print_binary(x);
      printf("\ny=");
      mpfr_print_binary(y);
      printf("\ngot      ");
      mpfr_print_binary(z);
      printf("\nexpected 0.1001001001101101010010100101011110000010111001001010100000000000E-529\n");
      exit(1);
    }

  mpfr_clears (x, y, z, (mpfr_ptr) 0);
}
