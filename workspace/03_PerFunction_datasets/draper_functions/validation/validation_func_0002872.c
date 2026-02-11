cpl_msg_info(const char *component, const char *format, ...)
{
    va_list     al;
    const char *c;

    _cpl_msg_init("cpl_msg_info");

    if (component == NULL)
        c = default_component;
    else
        c = component;

    if (format == NULL) {
        cpl_msg_info(c, default_format);
        return;
    }

    va_start(al, format);
    cpl_msg_out(CPL_MSG_INFO, c, 0, format, al);
    va_end(al);
}
