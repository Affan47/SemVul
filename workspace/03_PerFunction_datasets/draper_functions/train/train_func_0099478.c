create_consensus(ED4_group_manager *upper_group_manager) {


    ED4_group_manager *group_manager_for_child = upper_group_manager;

    if (is_group_manager()) {
        ED4_group_manager *group_manager = to_group_manager();

        group_manager->table().init(MAXSEQUENCECHARACTERLENGTH);
        group_manager_for_child = group_manager;

        if (loading) {
            if (aw_status(++status_count_curr/double(status_count_total)) == 1) {
                aw_closestatus();
                ED4_exit();
            }
        }
    }
    int i;
    for (i=0; i<children->members(); i++) {
        ED4_base *member = children->member(i);

        if (member->is_species_manager()){
            ED4_species_manager *species_manager = member->to_species_manager();
            ED4_terminal *sequence_data_terminal = species_manager->get_consensus_relevant_terminal();

            if (sequence_data_terminal) {
                int   db_pointer_len;
                char *db_pointer = sequence_data_terminal->resolve_pointer_to_string_copy(&db_pointer_len);
                group_manager_for_child->table().add(db_pointer, db_pointer_len);
                e4_assert(!group_manager_for_child->table().empty());
                free(db_pointer);
            }
        }else if (member->is_group_manager()){
            ED4_group_manager *sub_group = member->to_group_manager();

            sub_group->create_consensus(sub_group);
            e4_assert(sub_group!=upper_group_manager);
            upper_group_manager->table().add(sub_group->table());
#if defined(TEST_CHAR_TABLE_INTEGRITY)
            if (!sub_group->table().empty() && !sub_group->table().is_ignored()) {
                e4_assert(!upper_group_manager->table().empty());
            }
#endif
        }
        else if (member->is_manager()) {
            member->to_manager()->create_consensus(group_manager_for_child);
        }
    }
}
