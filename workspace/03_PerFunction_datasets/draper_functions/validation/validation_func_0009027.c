get_next_values(VALUE obj, struct enumerator *e)
{
    VALUE curr, vs;

    if (e->stop_exc)
	rb_exc_raise(e->stop_exc);

    curr = rb_fiber_current();

    if (!e->fib || !rb_fiber_alive_p(e->fib)) {
	next_init(obj, e);
    }

    vs = rb_fiber_resume(e->fib, 1, &curr);
    if (e->stop_exc) {
	e->fib = 0;
	e->dst = Qnil;
	e->lookahead = Qundef;
	e->feedvalue = Qundef;
	rb_exc_raise(e->stop_exc);
    }
    return vs;
}
