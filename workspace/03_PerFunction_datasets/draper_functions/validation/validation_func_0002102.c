update_pa_info(Pa_info *pa_info, Statement *stm)
{
    Pa_object *obj;
    Op_entry op_entry;
    Module_table *mpt = stm->pe_stm->block->module;

    if (pa_info->ptr_flg == TRUE) {
        pa_info = copy_pa_info(pa_info);
    }

    if (fspa_flg && stm->kill_pa_object != NULL) {
        op_entry = get_op_entry(stm->kill_pa_object);
        obj      = search_pa_object(&op_entry, pa_info->head);
        kill_pa_object(stm->kill_pa_object, pa_info);
    }

    for (obj = stm->merge_pa_object_list; obj != NULL; obj = obj->next) {
        merge_pa_object(obj, pa_info, mpt);
    }

    if (pa_output_info_ena) {
        fdump_pa_info_update(pa_info_fp, stm->pe_stm->block,
                             stm->kill_pa_object, stm->merge_pa_object_list);
    }

    return pa_info;
}
