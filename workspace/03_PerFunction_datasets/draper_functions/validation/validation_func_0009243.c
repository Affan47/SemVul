psgen_ellipse(GVJ_t * job, pointf * A, int filled)
{

    pointf AA[2];

    AA[0] = A[0];
    AA[1].x = A[1].x - A[0].x;
    AA[1].y = A[1].y - A[0].y;

    if (filled && job->obj->fillcolor.u.HSVA[3] > .5) {
	ps_set_color(job, &(job->obj->fillcolor));
	gvprintpointflist(job, AA, 2);
	gvputs(job, " ellipse_path fill\n");
    }
    if (job->obj->pencolor.u.HSVA[3] > .5) {
        ps_set_pen_style(job);
        ps_set_color(job, &(job->obj->pencolor));
	gvprintpointflist(job, AA, 2);
	gvputs(job, " ellipse_path stroke\n");
    }
}
