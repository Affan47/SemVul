sinfo_get_std_obs_values(cpl_propertylist* plist,
                       double* exptime,
                       double* airmass,
                       double* dRA,
                       double* dDEC)
{
   double airmass_start=0;
   double airmass_end=0;

   check_nomsg(*exptime=sinfo_pfits_get_exp_time(plist));
   airmass_start=sinfo_pfits_get_airmass_start(plist);
   airmass_end=sinfo_pfits_get_airmass_end(plist);
   *dRA=sinfo_pfits_get_ra(plist);
   *dDEC=sinfo_pfits_get_dec(plist);
   *airmass=0.5*(airmass_start+airmass_end);

 cleanup:
   return cpl_error_get_code();

}
