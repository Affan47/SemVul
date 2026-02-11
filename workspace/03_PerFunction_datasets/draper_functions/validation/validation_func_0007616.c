group_rsc_colocation_rh(resource_t * rsc_lh, resource_t * rsc_rh, rsc_colocation_t * constraint)
{
    GListPtr gIter = rsc_rh->children;
    group_variant_data_t *group_data = NULL;

    get_group_variant_data(group_data, rsc_rh);
    CRM_CHECK(rsc_lh->variant == pe_native, return);

    pe_rsc_trace(rsc_rh, "Processing RH of constraint %s", constraint->id);
    print_resource(LOG_DEBUG_3, "LHS", rsc_lh, TRUE);

    if (is_set(rsc_rh->flags, pe_rsc_provisional)) {
        return;

    } else if (group_data->colocated && group_data->first_child) {
        if (constraint->score >= INFINITY) {

            group_data->last_child->cmds->rsc_colocation_rh(rsc_lh, group_data->last_child,
                                                            constraint);
        } else {

            group_data->first_child->cmds->rsc_colocation_rh(rsc_lh, group_data->first_child,
                                                             constraint);
        }

        return;

    } else if (constraint->score >= INFINITY) {
        crm_config_err("%s: Cannot perform manditory colocation with"
                       " non-colocated group: %s", rsc_lh->id, rsc_rh->id);
        return;
    }

    for (; gIter != NULL; gIter = gIter->next) {
        resource_t *child_rsc = (resource_t *) gIter->data;

        child_rsc->cmds->rsc_colocation_rh(rsc_lh, child_rsc, constraint);
    }
}
