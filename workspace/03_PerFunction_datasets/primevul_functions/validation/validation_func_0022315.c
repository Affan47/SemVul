term_apply_lp_properties(struct lp_style_type *lp)
{


    int lt = lp->l_type;
    int dt = lp->d_type;
    t_dashtype custom_dash_pattern = lp->custom_dash_pattern;
    t_colorspec colorspec = lp->pm3d_color;

    if ((lp->flags & LP_SHOW_POINTS)) {


	if (lp->p_size < 0)
	    (*term->pointsize) (pointsize);
	else
	    (*term->pointsize) (lp->p_size);
    }


    (*term->linewidth) (lp->l_width);


    if (lt == LT_DEFAULT)
	;
    else


    if (LT_COLORFROMCOLUMN < lt && lt < 0)
	(*term->linetype) (lt);
    else if (term->set_color == null_set_color) {
	(*term->linetype) (lt-1);
	return;
    } else
	(*term->linetype) (LT_SOLID);


    if (lt == LT_NODRAW)
	return;


    if (lt == LT_AXIS)
	;
    else if (dt == DASHTYPE_CUSTOM)
	(*term->dashtype) (dt, &custom_dash_pattern);
    else if (dt == DASHTYPE_SOLID)
	(*term->dashtype) (dt, NULL);
    else if (dt >= 0)


	(*term->dashtype) (dt, NULL);


    apply_pm3dcolor(&colorspec);
}
