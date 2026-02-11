aucmd_restbuf(aco)
    aco_save_T	*aco;
{
    if (aco->save_curwin != NULL)
    {

#ifdef FEAT_WINDOWS
	if (win_valid(aco->save_curwin))
#endif
	{


	    if (curwin == aco->new_curwin
		    && buf_valid(aco->save_buf)
		    && aco->save_buf->b_ml.ml_mfp != NULL)
	    {
		--curbuf->b_nwindows;
		curbuf = aco->save_buf;
		curwin->w_buffer = curbuf;
		++curbuf->b_nwindows;
	    }

	    curwin = aco->save_curwin;
	    curbuf = curwin->w_buffer;
	}
    }
    else
    {

	if (buf_valid(aco->save_buf) && aco->save_buf->b_ml.ml_mfp != NULL)
	{
	    --curbuf->b_nwindows;
	    curbuf = aco->save_buf;
	    curwin->w_buffer = curbuf;
	    ++curbuf->b_nwindows;
	    curwin->w_cursor = aco->save_cursor;
	    check_cursor();

	    if (aco->save_topline <= curbuf->b_ml.ml_line_count)
	    {
		curwin->w_topline = aco->save_topline;
#ifdef FEAT_DIFF
		curwin->w_topfill = aco->save_topfill;
#endif
	    }
	    else
	    {
		curwin->w_topline = curbuf->b_ml.ml_line_count;
#ifdef FEAT_DIFF
		curwin->w_topfill = 0;
#endif
	    }
	}
    }
}
