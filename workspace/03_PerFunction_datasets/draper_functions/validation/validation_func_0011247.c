xkl_engine_query_tree(XklEngine * engine, Window w,
		      Window * root_out,
		      Window * parent_out,
		      Window ** children_out, guint * nchildren_out)
{
	gboolean result;
	unsigned int nc;

	result = (gboolean) XQueryTree(xkl_engine_get_display(engine),
				       w,
				       root_out,
				       parent_out, children_out, &nc);
	*nchildren_out = nc;

	if (!result) {
		xkl_debug(160,
			  "Could not get tree info for window "
			  WINID_FORMAT ": %d\n", w, result);
		xkl_last_error_message = "Could not get the tree info";
	}

	return result ? Success : FirstExtensionError;
}
