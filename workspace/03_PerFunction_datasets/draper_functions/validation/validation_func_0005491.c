handle_to_fp(CURL *handle)
{
    assert(stp);
    input_curl *result = (input_curl *)itab_query(stp, (itab_key_ty)handle);
    if (!result || !result->verify_handle(handle))
    {
	fatal_raw
	(
	    "%s: %d: handle %p gave file %p",
	    __FILE__,
	    __LINE__,
	    (void *)handle,
	    (void *)result
	);
    }
    return result;
}
