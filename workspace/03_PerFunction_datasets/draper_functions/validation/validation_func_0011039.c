rtl_dist_erlang(long *seed, long k, long mean)
{
      double r;
      long i;

      if (k > 0) {
            r = erlangian(seed, k, mean);
            if (r >= 0) {
                  i = (long) (r + 0.5);
            } else {
                  r = -r;
                  i = (long) (r + 0.5);
                  i = -i;
            }
      } else {
            vpi_printf("WARNING: K-stage erlangian distribution must have "
                       "a positive k\n");
            i = 0;
      }

      return i;
}
