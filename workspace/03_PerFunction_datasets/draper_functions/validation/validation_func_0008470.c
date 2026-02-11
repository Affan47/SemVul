inlet_free(t_inlet *x)
{
    t_object *y = x->i_owner;
    t_inlet *x2;
    if (y->ob_inlet == x) y->ob_inlet = x->i_next;
    else for (x2 = y->ob_inlet; x2; x2 = x2->i_next)
        if (x2->i_next == x)
    {
        x2->i_next = x->i_next;
        break;
    }
    t_freebytes(x, sizeof(*x));
}
