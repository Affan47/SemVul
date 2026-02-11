draw_signcolumn(wp)
    win_T *wp;
{
    return (wp->w_buffer->b_signlist != NULL
# ifdef FEAT_NETBEANS_INTG
			    || netbeans_active()
# endif
		    );
}
