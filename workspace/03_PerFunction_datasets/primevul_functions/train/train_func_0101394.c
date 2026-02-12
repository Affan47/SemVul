static void pp_verror(int severity, const char *fmt, va_list arg)
{
    char buff[BUFSIZ];
    MMacro *mmac = NULL;
    int delta = 0;


    if ((severity & ERR_MASK) < ERR_FATAL &&
	istk && istk->conds &&
	((severity & ERR_PP_PRECOND) ?
	 istk->conds->state == COND_NEVER :
	 !emitting(istk->conds->state)))
	return;


    if (!(severity & ERR_NOFILE) && istk && istk->mstk) {
        mmac = istk->mstk;

        while (mmac && !mmac->name)
            mmac = mmac->next_active, delta++;
    }

    if (mmac) {
	vsnprintf(buff, sizeof(buff), fmt, arg);

	nasm_set_verror(real_verror);
	nasm_error(severity, "(%s:%d) %s",
		   mmac->name, mmac->lineno - delta, buff);
	nasm_set_verror(pp_verror);
    } else {
        real_verror(severity, fmt, arg);
    }
}
