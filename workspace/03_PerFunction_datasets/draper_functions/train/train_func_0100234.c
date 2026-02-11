coord_statement(coord *co, axisdesc& xa, axisdesc& ya, axis log) {
    coord *c;

    if (co) c = co;
    else c = defcoord;

    if ( xa.which != none ) {
	c->xmin = xa.min;
	c->xmax = xa.max;
	c->xautoscale = 0;
    }
    if ( ya.which != none ) {
	c->ymin = ya.min;
	c->ymax = ya.max;
	c->yautoscale = 0;
    }
    if ( log != none ) c->logscale = log;
}
