epr_create_record_from_info(EPR_SRecordInfo* record_info)
{
    EPR_SRecord* record = NULL;
    EPR_SFieldInfo* field_info = NULL;
    uint field_infos_index = 0;


    if (record_info == NULL)
    {
        epr_set_err(e_err_out_of_memory,
                    "epr_create_record_from_info: out of memory");
        return NULL;
    }

    record = (EPR_SRecord*) calloc(1, sizeof(EPR_SRecord));
    if (record == NULL)
    {
        epr_set_err(e_err_out_of_memory,
                    "epr_create_record: out of memory");
        return NULL;
    }

    record->magic = EPR_MAGIC_RECORD;
    record->info = record_info;
    record->num_fields = record_info->field_infos->length;

    record->fields = (EPR_SField**) calloc(record->num_fields, sizeof(EPR_SField*));
    if (record->fields == NULL)
    {
        epr_set_err(e_err_out_of_memory,
                    "epr_create_record: out of memory");
        return NULL;
    }


    for (field_infos_index = 0; field_infos_index < record_info->field_infos->length; field_infos_index++)
    {
        field_info = (EPR_SFieldInfo*)epr_get_ptr_array_elem_at(record_info->field_infos, field_infos_index);
        record->fields[field_infos_index] = epr_create_field(field_info);
    }
    return record;
}
