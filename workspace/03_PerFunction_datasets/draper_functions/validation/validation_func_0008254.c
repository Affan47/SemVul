GC_generic_malloc_words_small(size_t lw, int k)
#else
     ptr_t GC_generic_malloc_words_small(lw, k)
     register word lw;
     register int k;
#endif
{
register ptr_t op;
DCL_LOCK_STATE;

    if (GC_have_errors) GC_print_all_errors();
    GC_INVOKE_FINALIZERS();
    DISABLE_SIGNALS();
    LOCK();
    op = GC_generic_malloc_words_small_inner(lw, k);
    UNLOCK();
    ENABLE_SIGNALS();
    return((ptr_t)op);
}
