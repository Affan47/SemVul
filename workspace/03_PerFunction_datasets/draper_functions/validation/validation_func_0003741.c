sharedsv_userlock_free(pTHX_ SV *sv, MAGIC *mg)
{
    user_lock *ul = (user_lock *) mg->mg_ptr;
    PERL_UNUSED_ARG(sv);
    assert(aTHX == PL_sharedsv_space);
    if (ul) {
        recursive_lock_destroy(aTHX_ &ul->lock);
        COND_DESTROY(&ul->user_cond);
        PerlMemShared_free(ul);
        mg->mg_ptr = NULL;
    }
    return (0);
}
