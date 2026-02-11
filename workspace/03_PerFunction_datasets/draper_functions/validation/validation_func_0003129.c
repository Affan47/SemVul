get_scan_list_res(GHashTable *hash,
                  gint *xres, gint *yres)
{
    NanoscopeValue *val;


    if ((val = g_hash_table_lookup(hash, "Samps/line")))
        *xres = GWY_ROUND(val->hard_value);
    if ((val = g_hash_table_lookup(hash, "Lines")))
        *yres = GWY_ROUND(val->hard_value);
    gwy_debug("Global xres, yres = %d, %d", *xres, *yres);
}
