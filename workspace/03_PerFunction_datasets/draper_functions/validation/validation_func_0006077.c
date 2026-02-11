ErrorHasReferents()
{
	return inlist(cur_error->er_buf->b_first, cur_error->er_text)
		&& inlist(perr_buf->b_first, cur_error->er_mess);
}
