main (int argc, char *argv[])
{
  int  limb_bits, nail_bits, numb_bits;

  if (argc != 4)
    {
      fprintf (stderr, "Usage: gen-bases <header|table> <limbbits> <nailbits>\n");
      exit (1);
    }

  limb_bits = atoi (argv[2]);
  nail_bits = atoi (argv[3]);

  if (limb_bits <= 0
      || nail_bits < 0
      || nail_bits >= limb_bits)
    {
      fprintf (stderr, "Invalid limb/nail bits: %d %d\n",
               limb_bits, nail_bits);
      exit (1);
    }
  numb_bits = limb_bits - nail_bits;

  generate (numb_bits);

  if (strcmp (argv[1], "header") == 0)
    header (numb_bits);
  else if (strcmp (argv[1], "table") == 0)
    table (numb_bits);
  else
    {
      fprintf (stderr, "Invalid header/table choice: %s\n", argv[1]);
      exit (1);
    }

  return 0;
}
