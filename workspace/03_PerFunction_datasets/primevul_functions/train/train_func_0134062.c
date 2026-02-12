test_length(header_field_info *hfinfo, tvbuff_t *tvb,
	    gint start, gint length, const guint encoding)
{
	gint size = length;

	if (!tvb)
		return;

	if ((hfinfo->type == FT_STRINGZ) ||
	    ((encoding & (ENC_VARIANT_MASK)) &&
	     (IS_FT_UINT(hfinfo->type) || IS_FT_INT(hfinfo->type)))) {


		if (length == -1)
			size = 0;
	}

	tvb_ensure_bytes_exist(tvb, start, size);
}
