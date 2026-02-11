xsh_obs_std_correct(cpl_frame* obs_std_star, xsh_star_flux_list * ref_std_star_list,
    cpl_frame* atmos_ext, HIGH_ABS_REGION * phigh,xsh_instrument* instrument )
{

  xsh_star_flux_list * corr_obs_std_star_list=NULL;
  double dRA = 0;
  double dDEC = 0;
  double airmass = 0;
  double exptime=0;


  check(xsh_frame_sci_get_ra_dec_airmass(obs_std_star, &dRA, &dDEC,&airmass));

  const char* filename = NULL;
  cpl_propertylist* plist = NULL;

  double gain = 0;


  check(filename = cpl_frame_get_filename(obs_std_star));
  check(plist = cpl_propertylist_load(filename, 0));

     airmass=xsh_pfits_get_airm_mean(plist);

  if (xsh_instrument_get_arm(instrument) == XSH_ARM_NIR) {

    gain = 1. / 2.12;

  } else {
    check_msg( gain = xsh_pfits_get_gain(plist), "Could not read gain factor");

  }
  check(exptime=xsh_pfits_get_exptime(plist));


  xsh_atmos_ext_list * atmos_ext_list = NULL;
  cpl_table* atmos_ext_tab = NULL;

  if (atmos_ext != NULL) {
    check( atmos_ext_list = xsh_atmos_ext_list_load( atmos_ext) );
    filename=cpl_frame_get_filename(atmos_ext);
    atmos_ext_tab=cpl_table_load(filename,1,0);
  } else {
    xsh_msg_warning(
        "Missing input %s_%s frame. Skip response and efficiency computation", XSH_ATMOS_EXT, xsh_instrument_arm_tostring(instrument));
  }


  double * atmos_lambda = NULL ;
  double * atmos_K = NULL ;

  check(xsh_interpolate_atm_ext(ref_std_star_list,atmos_ext_tab,instrument, &atmos_lambda,&atmos_K));

  XSH_ARM the_arm=xsh_instrument_get_arm(instrument);

  xsh_spectrum * obs_std_spectrum = NULL ;
  check( obs_std_spectrum = xsh_spectrum_load( obs_std_star));
  check(xsh_spectrum_correct(ref_std_star_list,
			     obs_std_spectrum,atmos_K,the_arm,
			     airmass,exptime,gain,&corr_obs_std_star_list));


  cleanup:
  xsh_free_table(&atmos_ext_tab);
  xsh_atmos_ext_list_free(&atmos_ext_list);
  xsh_free_propertylist(&plist);
  XSH_FREE( atmos_lambda ) ;
  XSH_FREE( atmos_K ) ;

  xsh_spectrum_free( &obs_std_spectrum ) ;
  return corr_obs_std_star_list;
}
