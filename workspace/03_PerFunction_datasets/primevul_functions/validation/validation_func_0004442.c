static void nasm_verror_common(int severity, const char *fmt, va_list args)
{
    char msg[1024];
    const char *pfx;

    switch (severity & (ERR_MASK|ERR_NO_SEVERITY)) {
    case ERR_WARNING:
        pfx = "warning: ";
        break;
    case ERR_NONFATAL:
        pfx = "error: ";
        break;
    case ERR_FATAL:
        pfx = "fatal: ";
        break;
    case ERR_PANIC:
        pfx = "panic: ";
        break;
    case ERR_DEBUG:
        pfx = "debug: ";
        break;
    default:
        pfx = "";
        break;
    }

    vsnprintf(msg, sizeof msg - 64, fmt, args);
    if (is_valid_warning(severity) && WARN_IDX(severity) != ERR_WARN_OTHER) {
        char *p = strchr(msg, '\0');
	snprintf(p, 64, " [-w+%s]", warnings[WARN_IDX(severity)].name);
    }

    if (!skip_this_pass(severity))
	fprintf(error_file, "%s%s\n", pfx, msg);


    if (severity & ERR_PP_LISTMACRO)
	return;


    lfmt->error(severity, pfx, msg);

    if (skip_this_pass(severity))
        return;

    if (severity & ERR_USAGE)
        want_usage = true;

    preproc->error_list_macros(severity);

    switch (severity & ERR_MASK) {
    case ERR_DEBUG:

        break;
    case ERR_WARNING:

        if (warning_is_error(severity))
            terminate_after_phase = true;
        break;
    case ERR_NONFATAL:
        terminate_after_phase = true;
        break;
    case ERR_FATAL:
        if (ofile) {
            fclose(ofile);
            if (!keep_all)
                remove(outname);
            ofile = NULL;
        }
        if (want_usage)
            usage();
        exit(1);
        break;
    case ERR_PANIC:
        fflush(NULL);

        if (abort_on_panic)
            abort();

        if (ofile) {
            fclose(ofile);
            if (!keep_all)
                remove(outname);
            ofile = NULL;
        }
        exit(3);
        break;
    }
}
