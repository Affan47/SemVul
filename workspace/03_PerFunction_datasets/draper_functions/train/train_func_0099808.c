xsh_parameters_pre_overscan( const char *recipe_id,
			     cpl_parameterlist * plist )
{
  cpl_parameter* p=NULL;
  char paramname[256];
  char recipename[256];

  XSH_ASSURE_NOT_NULL( recipe_id ) ;
  XSH_ASSURE_NOT_NULL( plist ) ;


  sprintf(recipename,"xsh.%s",recipe_id);
  sprintf(paramname,"%s.%s",recipename,"pre-overscan-corr");

  check(p = cpl_parameter_new_enum(paramname,CPL_TYPE_INT,
				   "pre-overscan correction."
                                   "0: no correction"
                                   "1: mean overscan correction"
                                   "2: mean prescan correction"
                                   "3: (mean pre+mean overscan)/2 correction"


				   ,recipename,1,
                                   4,0,1,2,3));

  check(cpl_parameter_set_alias(p,CPL_PARAMETER_MODE_CLI,
				"pre-overscan-corr"));
  check(cpl_parameterlist_append(plist,p));

 cleanup:
  return ;
}
