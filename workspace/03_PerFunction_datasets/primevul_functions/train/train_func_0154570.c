paste_option_changed(void)
{
    static int	old_p_paste = FALSE;
    static int	save_sm = 0;
    static int	save_sta = 0;
#ifdef FEAT_CMDL_INFO
    static int	save_ru = 0;
#endif
#ifdef FEAT_RIGHTLEFT
    static int	save_ri = 0;
    static int	save_hkmap = 0;
#endif
    buf_T	*buf;

    if (p_paste)
    {


	if (!old_p_paste)
	{

	    FOR_ALL_BUFFERS(buf)
	    {
		buf->b_p_tw_nopaste = buf->b_p_tw;
		buf->b_p_wm_nopaste = buf->b_p_wm;
		buf->b_p_sts_nopaste = buf->b_p_sts;
		buf->b_p_ai_nopaste = buf->b_p_ai;
		buf->b_p_et_nopaste = buf->b_p_et;
	    }


	    save_sm = p_sm;
	    save_sta = p_sta;
#ifdef FEAT_CMDL_INFO
	    save_ru = p_ru;
#endif
#ifdef FEAT_RIGHTLEFT
	    save_ri = p_ri;
	    save_hkmap = p_hkmap;
#endif

	    p_ai_nopaste = p_ai;
	    p_et_nopaste = p_et;
	    p_sts_nopaste = p_sts;
	    p_tw_nopaste = p_tw;
	    p_wm_nopaste = p_wm;
	}


	FOR_ALL_BUFFERS(buf)
	{
	    buf->b_p_tw = 0;
	    buf->b_p_wm = 0;
	    buf->b_p_sts = 0;
	    buf->b_p_ai = 0;
	    buf->b_p_et = 0;
	}


	p_sm = 0;
	p_sta = 0;
#ifdef FEAT_CMDL_INFO
# ifdef FEAT_WINDOWS
	if (p_ru)
	    status_redraw_all();
# endif
	p_ru = 0;
#endif
#ifdef FEAT_RIGHTLEFT
	p_ri = 0;
	p_hkmap = 0;
#endif

	p_tw = 0;
	p_wm = 0;
	p_sts = 0;
	p_ai = 0;
    }


    else if (old_p_paste)
    {

	FOR_ALL_BUFFERS(buf)
	{
	    buf->b_p_tw = buf->b_p_tw_nopaste;
	    buf->b_p_wm = buf->b_p_wm_nopaste;
	    buf->b_p_sts = buf->b_p_sts_nopaste;
	    buf->b_p_ai = buf->b_p_ai_nopaste;
	    buf->b_p_et = buf->b_p_et_nopaste;
	}


	p_sm = save_sm;
	p_sta = save_sta;
#ifdef FEAT_CMDL_INFO
# ifdef FEAT_WINDOWS
	if (p_ru != save_ru)
	    status_redraw_all();
# endif
	p_ru = save_ru;
#endif
#ifdef FEAT_RIGHTLEFT
	p_ri = save_ri;
	p_hkmap = save_hkmap;
#endif

	p_ai = p_ai_nopaste;
	p_et = p_et_nopaste;
	p_sts = p_sts_nopaste;
	p_tw = p_tw_nopaste;
	p_wm = p_wm_nopaste;
    }

    old_p_paste = p_paste;
}
