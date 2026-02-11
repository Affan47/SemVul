xsh_set_cd_matrix2d(cpl_propertylist* plist)
{
   double cdelt1=0;
   double cdelt2=0;


   check(cdelt1=xsh_pfits_get_cdelt1(plist));
   check(cdelt2=xsh_pfits_get_cdelt2(plist));
   check(xsh_pfits_set_cd11(plist,cdelt1));
   check(xsh_pfits_set_cd12(plist,0.));
   check(xsh_pfits_set_cd21(plist,0.));
   check(xsh_pfits_set_cd22(plist,cdelt2));

  cleanup:

   return cpl_error_get_code();

}
