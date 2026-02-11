ruby_float_step(VALUE from, VALUE to, VALUE step, int excl)
{
    if (TYPE(from) == T_FLOAT || TYPE(to) == T_FLOAT || TYPE(step) == T_FLOAT) {
	const double epsilon = DBL_EPSILON;
	double beg = NUM2DBL(from);
	double end = NUM2DBL(to);
	double unit = NUM2DBL(step);
	double n = (end - beg)/unit;
	double err = (fabs(beg) + fabs(end) + fabs(end-beg)) / fabs(unit) * epsilon;
	long i;

	if (isinf(unit)) {
	    if (unit > 0 ? beg <= end : beg >= end) rb_yield(DBL2NUM(beg));
	}
	else {
	    if (err>0.5) err=0.5;
	    n = floor(n + err);
	    if (!excl || ((long)n)*unit+beg < end) n++;
	    for (i=0; i<n; i++) {
		rb_yield(DBL2NUM(i*unit+beg));
	    }
	}
	return TRUE;
    }
    return FALSE;
}
