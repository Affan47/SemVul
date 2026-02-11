gpprintf (struct gf_printer *gp, const char *format, ...)
{
        va_list arg;
        char *str = NULL;
        int ret = 0;

        va_start (arg, format);
        ret = gf_vasprintf (&str, format, arg);
        va_end (arg);

        if (ret < 0)
                return ret;

        ret = gp->write (gp, str, ret);

        GF_FREE (str);

        return ret;
}
