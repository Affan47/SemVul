add_to_current( char *name,
                           TIC_P_DEFLT_TYPE fc_token,
			       fwtoken definer)
{
    if ( define_token )
{
	char *nu_name = strdup( name);

	save_current = *current_definitions;
	add_tic_entry( nu_name, FC_TOKEN_FUNC, fc_token,
			   definer, 0 , TRUE , NULL, current_definitions );
    }else{
	trace_create_failure( name, NULL, fc_token);
	warn_if_duplicate( name);
    }
}
