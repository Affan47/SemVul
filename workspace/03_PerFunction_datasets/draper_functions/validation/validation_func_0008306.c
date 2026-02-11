data_create_no_gc(int filename_index,
                          int line_num,
                          uint8 type,
                          void *arg1,
                          void *arg2,
                          void *arg3)
{
    data_t *new_data = create(filename_index,
                              line_num,
                              type,
                              arg1, arg2, arg3);

    if(IS_DATAERROR(new_data))
        eval_set_error(new_data);

    return new_data;
}
