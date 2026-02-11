cr_string_dup (CRString const *a_this)
{
	CRString *result = NULL ;
	g_return_val_if_fail (a_this, NULL) ;

	result = cr_string_new_from_gstring (a_this->stryng) ;
	if (!result) {
		cr_utils_trace_info ("Out of memory") ;
		return NULL ;
	}
	cr_parsing_location_copy (&result->location,
                                  &a_this->location) ;
        return result ;
}
