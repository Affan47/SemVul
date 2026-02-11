EXP_map_experiment(AW_root *aw_root, AW_CL scannerid)
{
    GB_transaction  dummy(GLOBAL_gb_main);
    GBDATA         *gb_experiment = EXP_get_current_experiment(GLOBAL_gb_main, aw_root);

    if (gb_experiment) awt_map_arbdb_scanner(scannerid, gb_experiment, 0, CHANGE_KEY_PATH_EXPERIMENTS);
}
