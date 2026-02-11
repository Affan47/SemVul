gp_enumerate_files_close(file_enum * pfen)
{
    gs_memory_t *mem = pfen->memory;

    if_debug0m('e', mem, "[e]file_enum:Cleanup\n");
    while (popdir(pfen))
        DO_NOTHING;
    gs_free_object(mem, (byte *) pfen->work,
                   "gp_enumerate_close(work)");
    gs_free_object(mem, (byte *) pfen->pattern,
                   "gp_enumerate_files_close(pattern)");
    gs_free_object(mem, pfen, "gp_enumerate_files_close");
}
