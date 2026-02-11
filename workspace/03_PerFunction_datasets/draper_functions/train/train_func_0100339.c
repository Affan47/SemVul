collect_gct_blocks (void)
{
    nat g;
    gen_workspace *ws;
    bdescr *bd, *prev;

    for (g = 0; g < RtsFlags.GcFlags.generations; g++) {
        ws = &gct->gens[g];


        if (ws->scavd_list != NULL) {
            ACQUIRE_SPIN_LOCK(&ws->gen->sync);

            ASSERT(gct->scan_bd == NULL);
            ASSERT(countBlocks(ws->scavd_list) == ws->n_scavd_blocks);

            prev = NULL;
            for (bd = ws->scavd_list; bd != NULL; bd = bd->link) {
                ws->gen->n_words += bd->free - bd->start;
                prev = bd;
            }
            if (prev != NULL) {
                prev->link = ws->gen->blocks;
                ws->gen->blocks = ws->scavd_list;
            }
            ws->gen->n_blocks += ws->n_scavd_blocks;

            ws->scavd_list = NULL;
            ws->n_scavd_blocks = 0;

            RELEASE_SPIN_LOCK(&ws->gen->sync);
        }
    }
}
