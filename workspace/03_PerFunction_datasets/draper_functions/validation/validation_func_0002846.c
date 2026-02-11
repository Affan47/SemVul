sinfo_utl_bp_mask_add(cpl_parameterlist *config, cpl_frameset *sof)
{
  cpl_frameset* ref_set=NULL;
  int n=0;

  sinfo_msg("Welcome to SINFONI Pipeline release %d.%d.%d",
        SINFONI_MAJOR_VERSION,SINFONI_MINOR_VERSION,SINFONI_MICRO_VERSION);

   if(sinfo_dfs_set_groups(sof)) {
       sinfo_msg_error("Cannot indentify RAW and CALIB frames") ;
   }

    n=cpl_frameset_get_size(sof);
    if(n<1) {
      sinfo_msg_error("Empty input frame list!");
      goto cleanup ;
    }

   check_nomsg(ref_set=cpl_frameset_duplicate(sof));
   ck0_nomsg(sinfo_new_add_bp_map(cpl_func,config,sof,ref_set));

 cleanup:
   sinfo_free_frameset(&ref_set);
  if (cpl_error_get_code() != CPL_ERROR_NONE) {
    return -1;
  } else {
    return 0;
  }


}
