do_arc(
    int cx, int cy,
    double radius,
    double arc_start, double arc_end,
    int style, TBOOLEAN wedge)
{
    gpiPoint vertex[250];
    int i, segments;
    double aspect;
    TBOOLEAN complete_circle;


    while (arc_start < 0)
	arc_start += 360.;
    while (arc_end > 360.)
	arc_end -= 360.;


    while (arc_end < arc_start)
	arc_end += 360.;


#   define INC 3.
    segments = (arc_end - arc_start) / INC;
    if (segments < 1)
	segments = 1;


    aspect = (double)term->v_tic / (double)term->h_tic;
    for (i=0; i<segments; i++) {
	vertex[i].x = cx + cos(DEG2RAD * (arc_start + i*INC)) * radius;
	vertex[i].y = cy + sin(DEG2RAD * (arc_start + i*INC)) * radius * aspect;
    }
#   undef INC
    vertex[segments].x = cx + cos(DEG2RAD * arc_end) * radius;
    vertex[segments].y = cy + sin(DEG2RAD * arc_end) * radius * aspect;

    if (fabs(arc_end - arc_start) > .1
    &&  fabs(arc_end - arc_start) < 359.9) {
	vertex[++segments].x = cx;
	vertex[segments].y = cy;
	vertex[++segments].x = vertex[0].x;
	vertex[segments].y = vertex[0].y;
	complete_circle = FALSE;
    } else
	complete_circle = TRUE;

    if (style) {
	gpiPoint fillarea[250];
	int in;

	clip_polygon(vertex, fillarea, segments, &in);
	fillarea[0].style = style;
	if (term->filled_polygon)
	    term->filled_polygon(in, fillarea);

    } else {
	if (!wedge && !complete_circle)
	    segments -= 2;
	draw_clip_polygon(segments+1, vertex);
    }
}
