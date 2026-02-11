get_rhs_rng_sense(LPdata *lp_data)
{
   const double *rowub = lp_data->si->getRowUpper();
   const double *rowlb = lp_data->si->getRowLower();
   double *mip_rhs = lp_data->mip->rhs;
   double *mip_rngval = lp_data->mip->rngval;
   char *mip_sense = lp_data->mip->sense;

   for (int i=0;i<lp_data->m;i++) {
      if (rowub[i]>=SYM_INFINITY) {
         mip_sense[i] = 'G';
         mip_rhs[i] = rowlb[i];
      }
      else if (rowlb[i]<=-SYM_INFINITY) {
         mip_sense[i] = 'L';
         mip_rhs[i] = rowub[i];
      }
      else {
         mip_sense[i] = 'R';
         mip_rhs[i] = rowub[i];
         mip_rngval[i] = rowub[i]-rowlb[i];
      }
   }
}
