generate_rsa_params (void)
{
  if (gnutls_rsa_params_init (&rsa_params) < 0)
    {
      fprintf (stderr, "Error in rsa parameter initialization\n");
      exit (1);
    }


  printf ("Generating temporary RSA parameters. Please wait...\n");
  fflush (stdout);

  if (gnutls_rsa_params_generate2 (rsa_params, 512) < 0)
    {
      fprintf (stderr, "Error in rsa parameter generation\n");
      exit (1);
    }

  return 0;
}
