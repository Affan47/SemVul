get_adep(Block *src,
         Block *dst,
         dep_type type,
         Array_def_use_table_semnode *du)
{
    Adep *adep;
    extern Boolean rp1_dma_force_restrict;

    if (du == NULL) {
        return NULL;
    }

    adep = zcalloc(1, sizeof(Adep));

    adep->type = type;
    adep->entry = du->entry;
    adep->du = du;
    adep->src = src;
    adep->dst = dst;

    adep->sched_time = -1.0;

    adep->check_count = 0;

    if (rp1_dma_force_restrict) {

        Block *bpt;
        if (src != NULL) {
            bpt = (src->cmp_localize) ? src : dst;
        } else {
            bpt = dst;
        }
        restrict_array_du_size_multi4byte_body(adep->du, bpt, FALSE);
    }

    return adep;
}
