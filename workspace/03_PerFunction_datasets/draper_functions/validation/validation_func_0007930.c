xsh_wavecal_get_parameters( cpl_parameterlist* parameters,
					xsh_follow_arclines_param * par )
{
  check( par->range = xsh_parameters_wavecal_range_get( RECIPE_ID,
							parameters));
  check( par->margin = xsh_parameters_wavecal_margin_get( RECIPE_ID,
							  parameters));
  check( par->s_n_min = xsh_parameters_wavecal_s_n_get( RECIPE_ID,
							parameters));
  check( par->tilt_clipping = xsh_parameters_clipping_tilt_get( RECIPE_ID,
							   parameters));
  check( par->specres_clipping = xsh_parameters_clipping_specres_get( RECIPE_ID,
                                                           parameters));
  cleanup:
    return ;
}
