ompfbe_stasche_write_decl(fsbe_context *cx, Hmdf_table *hmdf, int clustering_number)
{
    stasche_write_decl_vars(cx, hmdf);
    stasche_write_decl_common(cx, hmdf, clustering_number);
    if (opt_volatile)
        stasche_write_decl_volatile(cx, hmdf);
}
