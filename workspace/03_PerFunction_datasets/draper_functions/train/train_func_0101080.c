_z_factor_SQUFOF(unsigned long n)
{
   unsigned long sqroot = z_intsqrt(n);
   unsigned long p = sqroot;
   unsigned long q = n - sqroot*sqroot;

   if (q == 0)
   {
      return sqroot;
   }

   unsigned long l = 1 + 2*z_intsqrt(2*p);
   unsigned long l2 = l/2;
   unsigned long iq, pnext;
   unsigned long qarr[50];
   unsigned long qupto = 0;
   unsigned long qlast = 1;
   unsigned long i, j, t, r;

   for (i = 0; i < SQUFOF_ITERS; i++)
   {
      iq = (sqroot + p)/q;
      pnext = iq*q - p;
      if (q <= l)
      {
         if ((q & 1) == 0)
         {
            qarr[qupto] = q/2;
            qupto++;
            if (qupto >= 50) return 0;
         } else if (q <= l2)
         {
            qarr[qupto] = q;
            qupto++;
            if (qupto >= 50) return 0;
         }
      }
      t = qlast + iq*(p - pnext);
	  qlast = q;
	  q = t;
	  p = pnext;
	  if ((i&1) == 1) continue;
	  if (!z_issquare(q)) continue;
	  r = z_intsqrt(q);
	  if (qupto == 0) break;
	  for (j = 0; j < qupto; j++)
         if (r == qarr[j]) goto cont;
      break;
      cont: ; if (r == 1) return 0;
   }

   if (i == SQUFOF_ITERS) return 0;

   qlast = r;
   p = p + r*((sqroot - p)/r);
   q = (n - p*p)/qlast;

   for (j = 0; j < SQUFOF_ITERS; j++)
   {
	  iq = (sqroot + p)/q;
	  pnext = iq*q - p;
	  if (p == pnext) break;
	  t = qlast + iq*(p - pnext);
	  qlast = q;
	  q = t;
	  p = pnext;
   }

   if ((q & 1) == 0) q /= 2;

   return q;
}
