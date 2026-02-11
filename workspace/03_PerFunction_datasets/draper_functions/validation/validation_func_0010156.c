pop_source( void )
{
    bool retval = TRUE;

    if ( saved_source != NULL )
    {
	retval = FALSE;
	if ( need_to_pop_source )
	{
	    need_to_pop_source = FALSE;
	}else{
	    if ( saved_source->pause_before_pop )
	    {
	        need_to_pop_source = TRUE;
		return( retval);
	    }
	}

	if ( saved_source->resump_func != NULL )
	{
	    saved_source->resump_func( saved_source->resump_param);
	}
	report_multiline = saved_source->sav_rep_multlin;
	lineno = saved_source->old_lineno ;
	iname = saved_source->old_iname ;
	end = saved_source->old_end ;
	pc = saved_source->old_pc ;
	start = saved_source->old_start ;

	drop_source();
    }
    return( retval);
}
