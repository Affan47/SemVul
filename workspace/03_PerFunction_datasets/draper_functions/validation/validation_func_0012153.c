file_find_decoder (const char * filename, bool_t fast)
{
    ProbeState state;

    AUDDBG ("Probing %s.\n", filename);
    state.plugin = NULL;
    state.filename = filename;
    state.handle = NULL;
    state.failed = FALSE;

    probe_by_scheme (& state);

    if (state.plugin != NULL)
        goto DONE;

    probe_by_extension (& state);

    if (state.plugin != NULL || fast)
        goto DONE;

    probe_by_mime (& state);

    if (state.plugin != NULL)
        goto DONE;

    probe_by_content (& state);

DONE:
    if (state.handle != NULL)
        vfs_fclose (state.handle);

    if (state.plugin != NULL)
        AUDDBG ("Probe succeeded: %s\n", plugin_get_name (state.plugin));
    else
        AUDDBG ("Probe failed.\n");

    return state.plugin;
}
