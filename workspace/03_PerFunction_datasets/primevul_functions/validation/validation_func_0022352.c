do_arrow(
    unsigned int usx, unsigned int usy,
    unsigned int uex, unsigned int uey,
    int headstyle)
{

    int sx = (int)usx;
    int sy = (int)usy;
    int ex = (int)uex;
    int ey = (int)uey;

    struct termentry *t = term;
    double len_tic = ((double) (t->h_tic + t->v_tic)) / 2.0;


    double dx = sx - ex;
    double dy = sy - ey;
    double len_arrow = sqrt(dx * dx + dy * dy);
    gpiPoint head_points[5];
    int xm = 0, ym = 0;
    BoundingBox *clip_save;


    clip_save = clip_area;
    if (term->flags & TERM_CAN_CLIP)
	clip_area = NULL;
    else
	clip_area = &canvas;


    if ((headstyle & BOTH_HEADS) != NOHEAD && fabs(len_arrow) >= DBL_EPSILON) {
	int x1, y1, x2, y2;
	if (curr_arrow_headlength <= 0) {

	    double coeff_shortest = len_tic * HEAD_SHORT_LIMIT / len_arrow;
	    double coeff_longest = len_tic * HEAD_LONG_LIMIT / len_arrow;
	    double head_coeff = GPMAX(coeff_shortest,
				      GPMIN(HEAD_COEFF, coeff_longest));

	    x1 = (int) ((COS15 * dx - SIN15 * dy) * head_coeff);
	    y1 = (int) ((SIN15 * dx + COS15 * dy) * head_coeff);
	    x2 = (int) ((COS15 * dx + SIN15 * dy) * head_coeff);
	    y2 = (int) ((-SIN15 * dx + COS15 * dy) * head_coeff);

	    xm = (int) ((x1 + x2)/2);
	    ym = (int) ((y1 + y2)/2);
	} else {


	    double alpha = curr_arrow_headangle * DEG2RAD;
	    double beta = curr_arrow_headbackangle * DEG2RAD;
	    double phi = atan2(-dy,-dx);
	    double backlen, effective_length;
	    double dx2, dy2;

	    effective_length = curr_arrow_headlength;
	    if (!curr_arrow_headfixedsize && (curr_arrow_headlength > len_arrow/2.)) {
		effective_length = len_arrow/2.;
		alpha = atan(tan(alpha)*((double)curr_arrow_headlength/effective_length));
		beta = atan(tan(beta)*((double)curr_arrow_headlength/effective_length));
	    }
	    backlen = sin(alpha) / sin(beta);


	    x1 = -(int)(effective_length * cos( alpha - phi ));
	    y1 =  (int)(effective_length * sin( alpha - phi ));

	    dx2 = -effective_length * cos( phi + alpha );
	    dy2 = -effective_length * sin( phi + alpha );
	    x2 = (int) (dx2);
	    y2 = (int) (dy2);

	    xm = (int) (dx2 + backlen*effective_length * cos( phi + beta ));
	    ym = (int) (dy2 + backlen*effective_length * sin( phi + beta ));
	}

	if ((headstyle & END_HEAD) && !clip_point(ex, ey)) {
	    head_points[0].x = ex + xm;
	    head_points[0].y = ey + ym;
	    head_points[1].x = ex + x1;
	    head_points[1].y = ey + y1;
	    head_points[2].x = ex;
	    head_points[2].y = ey;
	    head_points[3].x = ex + x2;
	    head_points[3].y = ey + y2;
	    head_points[4].x = ex + xm;
	    head_points[4].y = ey + ym;
	    if (!((headstyle & SHAFT_ONLY))) {
		if (curr_arrow_headfilled >= AS_FILLED) {

		    head_points->style = FS_OPAQUE;
		    if (t->filled_polygon)
			(*t->filled_polygon) (5, head_points);
		}

		if (curr_arrow_headfilled == AS_NOFILL) {
		    draw_clip_polygon(3, head_points+1);
		} else if (curr_arrow_headfilled != AS_NOBORDER) {
		    draw_clip_polygon(5, head_points);
		}
	    }
	}


	if ((headstyle & BACKHEAD) && !clip_point(sx,sy)) {
	    head_points[0].x = sx - xm;
	    head_points[0].y = sy - ym;
	    head_points[1].x = sx - x1;
	    head_points[1].y = sy - y1;
	    head_points[2].x = sx;
	    head_points[2].y = sy;
	    head_points[3].x = sx - x2;
	    head_points[3].y = sy - y2;
	    head_points[4].x = sx - xm;
	    head_points[4].y = sy - ym;
	    if (!((headstyle & SHAFT_ONLY))) {
		if (curr_arrow_headfilled >= AS_FILLED) {

		    head_points->style = FS_OPAQUE;
		    if (t->filled_polygon)
			(*t->filled_polygon) (5, head_points);
		}

		if (curr_arrow_headfilled == AS_NOFILL) {
		    draw_clip_polygon(3, head_points+1);
		} else if (curr_arrow_headfilled != AS_NOBORDER) {
		    draw_clip_polygon(5, head_points);
		}
	    }
	}
    }


    if ((headstyle & BACKHEAD)
    &&  (fabs(len_arrow) >= DBL_EPSILON) && (curr_arrow_headfilled != AS_NOFILL) ) {
	sx -= xm;
	sy -= ym;
    }
    if ((headstyle & END_HEAD)
    &&  (fabs(len_arrow) >= DBL_EPSILON) && (curr_arrow_headfilled != AS_NOFILL) ) {
	ex += xm;
	ey += ym;
    }


    if (!((headstyle & HEADS_ONLY)))
	draw_clip_line(sx, sy, ex, ey);


    clip_area = clip_save;
}
