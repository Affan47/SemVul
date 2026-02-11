point_offset(const fn_call& fn)
{
    as_object* ptr = ensure<ValidThis>(fn);

    as_value x, y;
    ptr->get_member(NSV::PROP_X, &x);
    ptr->get_member(NSV::PROP_Y, &y);

    as_value xoff, yoff;

    if ( fn.nargs ) {
        xoff = fn.arg(0);
        if ( fn.nargs > 1 ) yoff = fn.arg(1);
    }

    VM& vm = getVM(fn);
    newAdd(x, xoff, vm);
    newAdd(y, yoff, vm);

    ptr->set_member(NSV::PROP_X, x);
    ptr->set_member(NSV::PROP_Y, y);

    return as_value();
}
