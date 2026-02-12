ind_find_start_CORS(linenr_T *is_raw)
{
    static pos_T comment_pos_copy;
    pos_T	*comment_pos;
    pos_T	*rs_pos;

    comment_pos = find_start_comment(curbuf->b_ind_maxcomment);
    if (comment_pos != NULL)
    {


	comment_pos_copy = *comment_pos;
	comment_pos = &comment_pos_copy;
    }
    rs_pos = find_start_rawstring(curbuf->b_ind_maxcomment);


    if (comment_pos == NULL || (rs_pos != NULL
					     && LT_POS(*rs_pos, *comment_pos)))
    {
	if (is_raw != NULL && rs_pos != NULL)
	    *is_raw = rs_pos->lnum;
	return rs_pos;
    }
    return comment_pos;
}
