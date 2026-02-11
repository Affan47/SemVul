ldbm_usn_init(struct ldbminfo  *li)
{
    Slapi_DN *sdn = NULL;
    void *node = NULL;
    int rc = 0;
    Slapi_Backend *be = NULL;
    PRUint64 last_usn = 0;
    PRUint64 global_last_usn = INITIALUSN;
    int isglobal = config_get_entryusn_global();
    int isfirst = 1;


    if (!plugin_enabled("USN", li->li_identity)) {
        goto bail;
    }


    for ( sdn = slapi_get_first_suffix( &node, 0 ); sdn != NULL;
          sdn = slapi_get_next_suffix_ext( &node, 0 )) {
        be = slapi_mapping_tree_find_backend_for_sdn(sdn);
        slapi_log_error(SLAPI_LOG_BACKLDBM, "ldbm_usn_init",
                    "backend: %s%s\n", be->be_name, isglobal?" (global mode)":"");
        rc = usn_get_last_usn(be, &last_usn);
        if (0 == rc) {
            if (isglobal) {
                if (isfirst) {
                    li->li_global_usn_counter = slapi_counter_new();
                    isfirst = 0;
                }

                be->be_usn_counter = li->li_global_usn_counter;


                if ((global_last_usn == INITIALUSN) ||
                   ((last_usn != INITIALUSN) && (global_last_usn < last_usn))) {
                    global_last_usn = last_usn;
                }
                slapi_counter_set_value(be->be_usn_counter, global_last_usn);

                slapi_counter_increment(be->be_usn_counter);
            } else {
                be->be_usn_counter = slapi_counter_new();
                slapi_counter_set_value(be->be_usn_counter, last_usn);

                slapi_counter_increment(be->be_usn_counter);
            }
        }
    }
bail:
    return;
}
