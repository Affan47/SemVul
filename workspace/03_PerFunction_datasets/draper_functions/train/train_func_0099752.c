scm_valid_environment_extension_lengthp(scm_int_t formals_len,
                                        scm_int_t actuals_len)
{
    if (SCM_LISTLEN_ERRORP(formals_len))
        return scm_false;
    if (SCM_LISTLEN_DOTTEDP(formals_len)) {
        formals_len = SCM_LISTLEN_DOTTED(formals_len);
        if (SCM_LISTLEN_PROPERP(actuals_len))
            return (formals_len <= actuals_len);


        if (SCM_LISTLEN_DOTTEDP(actuals_len))
            return (formals_len <= SCM_LISTLEN_DOTTED(actuals_len));


        if (SCM_LISTLEN_CIRCULARP(actuals_len))
            return scm_true;
    }
    return (formals_len == actuals_len);
}
