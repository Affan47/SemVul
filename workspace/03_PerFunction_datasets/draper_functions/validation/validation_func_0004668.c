localize_stasche()
{
    Stasche_localize_table *localize_table;

    for (localize_table = stasche_localize_head.table_head;
         localize_table != NULL;
         localize_table = localize_table->next) {
        make_local_array(localize_table);
        if (plps_flag) {
            gen_plps(localize_table);
        } else {
            gen_dt(localize_table);
        }
        rename_array_entry(localize_table);
    }

    for (current_stasche_table = stasche_head;
         current_stasche_table != NULL;
         current_stasche_table = current_stasche_table->next) {
        proc_cmp_localize_blocks(current_stasche_table->hmdf->block->inner);
    }
}
