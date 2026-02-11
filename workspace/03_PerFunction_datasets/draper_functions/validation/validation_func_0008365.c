parser_create(struct ini_cfgobj *co,
                         FILE *file,
                         const char *config_filename,
                         int error_level,
                         uint32_t collision_flags,
                         uint32_t parse_flags,
                         struct parser_obj **po)
{
    int error = EOK;
    struct parser_obj *new_po = NULL;
    unsigned count = 0;

    TRACE_FLOW_ENTRY();


    if ((!po) ||
        (!co) ||
        (!(co->cfg)) ||
        (!file) ||
        (!config_filename)) {
        TRACE_ERROR_NUMBER("Invalid argument", EINVAL);
        return EINVAL;
    }

    error = col_get_collection_count(co->cfg, &count);
    if (error) {
        TRACE_ERROR_NUMBER("Failed to check object size", error);
        return error;
    }

    if (count != 1) {
        TRACE_ERROR_NUMBER("Configuration is not empty", EINVAL);
        return EINVAL;
    }

    new_po = malloc(sizeof(struct parser_obj));
    if (!new_po) {
        TRACE_ERROR_NUMBER("No memory", ENOMEM);
        return ENOMEM;
    }


    new_po->file = file;
    new_po->el = co->error_list;
    new_po->filename = config_filename;
    new_po->error_level = error_level;
    new_po->collision_flags = collision_flags;
    new_po->parse_flags = parse_flags;
    new_po->boundary = co->boundary;
    new_po->co = co;


    new_po->sec = NULL;
    new_po->merge_sec = NULL;
    new_po->ic = NULL;
    new_po->last_error = 0;
    new_po->linenum = 0;
    new_po->keylinenum = 0;
    new_po->seclinenum = 0;
    new_po->last_read = NULL;
    new_po->last_read_len = 0;
    new_po->key = NULL;
    new_po->key_len = 0;
    new_po->raw_lines = NULL;
    new_po->raw_lengths = NULL;
    new_po->ret = EOK;
    new_po->merge_key = NULL;
    new_po->merge_vo = NULL;
    new_po->merge_error = 0;
    new_po->top = NULL;
    new_po->queue = NULL;


    error = col_create_collection(&(new_po->top),
                                  INI_CONFIG_NAME,
                                  COL_CLASS_INI_CONFIG);
    if (error) {
        TRACE_ERROR_NUMBER("Failed to create top collection", error);
        parser_destroy(new_po);
        return error;
    }


    error = col_create_queue(&(new_po->queue));
    if (error) {
        TRACE_ERROR_NUMBER("Failed to create queue", error);
        parser_destroy(new_po);
        return error;
    }

    error = col_enqueue_unsigned_property(new_po->queue,
                                          PARSE_ACTION,
                                          PARSE_READ);
    if (error) {
        TRACE_ERROR_NUMBER("Failed to create queue", error);
        parser_destroy(new_po);
        return error;
    }

    *po = new_po;

    TRACE_FLOW_EXIT();
    return error;
}
