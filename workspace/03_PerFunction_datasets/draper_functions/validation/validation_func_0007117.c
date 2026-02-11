textfield_maxscroll(const fn_call& fn)
{
    TextField* text = ensure<IsDisplayObject<TextField> >(fn);

    LOG_ONCE(log_unimpl(_("TextField.maxscroll is not complete")));

    if (!fn.nargs) {

        return as_value(text->getMaxScroll());
    }

    return as_value();
}
