score_clamp_prob(oligo)
struct oligo_list *oligo;
{
   int pos, res, clamp_len, ipos;
   double dtemp, maxwt;

   clamp_len = oligo->clamp_first - oligo->clamp_last + 1;

   oligo->clamp_prob = 0.0;
   ipos = 0;
   for (pos = oligo->clamp_first; pos >= oligo->clamp_last; pos--)
   {
      maxwt = 0.0;
      for (res=0; res < 4; res++)
      {
         if (oligo->pssm->weights[res][pos] > maxwt)
             maxwt = oligo->pssm->weights[res][pos];
      }
      ipos++;
      dtemp =  ((double) clamp_len + 1 - ipos) / ((double) clamp_len);


      oligo->clamp_prob += ( dtemp * maxwt );
   }
   dtemp = ((double) (clamp_len + 1)) / 2.0 ;
   oligo->clamp_prob /= dtemp;

}
