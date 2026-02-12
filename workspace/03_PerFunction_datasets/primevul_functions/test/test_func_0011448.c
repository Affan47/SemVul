adjust_cursor(oparg_T *oap)
{


    if (curwin->w_cursor.col > 0 && gchar_cursor() == NUL
		&& (!VIsual_active || *p_sel == 'o')
		&& !virtual_active() && (get_ve_flags() & VE_ONEMORE) == 0)
    {
	--curwin->w_cursor.col;

	if (has_mbyte)
	    mb_adjust_cursor();
	oap->inclusive = TRUE;
    }
}
