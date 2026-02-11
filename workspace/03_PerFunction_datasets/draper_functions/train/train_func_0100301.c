multi_species_man_consensus_id_starts_with(ED4_base *base, AW_CL cl_start) {
    ED4_multi_species_manager *ms_man = base->to_multi_species_manager();
    char *start = (char*)cl_start;
    ED4_base *consensus = ms_man->search_spec_child_rek(ED4_L_SPECIES);

    if (consensus) {
        ED4_base *consensus_name = consensus->search_spec_child_rek(ED4_L_SPECIES_NAME);

        if (consensus_name) {
            if (strncmp(consensus_name->id, start, strlen(start))==0) {
                ED4_multi_species_manager *cons_ms_man = consensus_name->get_parent(ED4_L_MULTI_SPECIES)->to_multi_species_manager();
                return cons_ms_man==ms_man;
            }
        }
    }

    return 0;
}
