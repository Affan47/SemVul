static bool pp_suppress_error(errflags severity)
{


    if (istk && istk->conds &&
	((severity & ERR_PP_PRECOND) ?
	 istk->conds->state == COND_NEVER :
	 !emitting(istk->conds->state)))
        return true;

    return false;
}
