define_power_inst_for_dynamic_layer(Ctrl_task *ctrl_task,
                                    int pe_no, Ctrl_task ***ctrl_tasks)
{
    List *inner = ctrl_task_get_inner(ctrl_task);
    int i, l = list_length(inner);

    if (ctrl_task_get_fv(ctrl_task) == ANY) {
        for (i = 0; i < l; i++) {
            Ctrl_task *c = (Ctrl_task *)list_nth_data(inner, i);
            fv_kind fv = ctrl_task_get_fv(c);

            if (fv != ANY)
                ctrl_task_set_insert_fv(c, TRUE);
        }
    }

    for (i = 0; i < l; i++) {
        Ctrl_task *c = (Ctrl_task *)list_nth_data(inner, i);

        if ( ctrl_task_get_inner(c) != NULL)
            define_power_inst_for_layer_block(c, pe_no, ctrl_tasks);
    }
}
