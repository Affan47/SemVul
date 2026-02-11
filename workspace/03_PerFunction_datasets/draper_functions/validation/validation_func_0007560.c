openssl_seed_prng (void)
{
   const char *names[]  = { "/dev/urandom", "/dev/random", NULL };
   int i;


   for (i = 0; names[i]; i++) {
      if (RAND_load_file(names[i], 1024) != -1) {

         return 1;
      }
   }


   return 0;
}
