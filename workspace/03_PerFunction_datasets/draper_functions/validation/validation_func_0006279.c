fig_textspan(GVJ_t * job, pointf p, textspan_t * span)
{
    obj_state_t *obj = job->obj;
    PostscriptAlias *pA;

    int object_code = 4;
    int sub_type = 0;
    int color = obj->pencolor.u.index;
    int depth = Depth;
    int pen_style = 0;
    int font = -1;
    double font_size = span->font->size * job->zoom;
    double angle = job->rotation ? (M_PI / 2.0) : 0.0;
    int font_flags = 6;


    double height = 0.0;
    double length = 0.0;

    pA = span->font->postscript_alias;
    if (pA)
	font = pA->xfig_code;

    switch (span->just) {
    case 'l':
        sub_type = 0;
        break;
    case 'r':
        sub_type = 2;
        break;
    default:
    case 'n':
        sub_type = 1;
        break;
    }

    gvprintf(job,
            "%d %d %d %d %d %d %.1f %.4f %d %.1f %.1f %d %d %s\\001\n",
            object_code, sub_type, color, depth, pen_style, font,
            font_size, angle, font_flags, height, length, ROUND(p.x), ROUND(p.y),
            fig_string(span->str));
}
