init_output( const char *in_name, const char *out_name )
{


	if( out_name != NULL )
	{
		oname = strdup( out_name );
	}else{
		oname = extend_filename( in_name, ".fc");
	}


	olen = OUTPUT_SIZE;
	ostart=safe_malloc(olen, "initting output buffer");

	init_emit();

	printf("Binary output to %s ", oname);
	if ( fload_list )
	{
	    load_list_name = extend_filename( oname, ".fl");
	    load_list_file = fopen( load_list_name,"w");
	    printf("  FLoad-list to %s ", load_list_name);
	}
	if ( dependency_list )
	{
	    depncy_list_name = extend_filename( oname, ".P");
	    depncy_file = fopen( depncy_list_name,"w");
	    printf("  Dependency-list to %s ", depncy_list_name);
	}
	printf("\n");

	add_to_load_lists( in_name);


	FFLUSH_STDOUT


	{

	    char *temp_iname = iname;
	    iname = NULL;

	    finish_incl_list_scan( TRUE);

	    if ( fload_list && (load_list_file == NULL) )
	    {
	    	could_not_open( TKERROR, load_list_name, "Load-List");
		free( load_list_name);
	    }
	    if ( dependency_list && (depncy_file == NULL) )
	    {
	    	could_not_open( TKERROR, depncy_list_name,
		    "Dependency-List");
		free( depncy_list_name);
}

	    if ( fload_list || dependency_list )
	    {
		missing_list_name = extend_filename( oname, ".fl.missing");
		missing_list_file = fopen( missing_list_name,"w");
		no_files_missing = TRUE;

		if ( missing_list_file == NULL )
		{
		    could_not_open( WARNING, missing_list_name,
			"Missing-Files List" );
	            free( missing_list_name);
		}
	    }
	    iname = temp_iname;
	}
	abs_token_no = 1;
}
