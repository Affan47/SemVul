uish_cmd_free(struct uish_comm_s * comm) {
    if (NULL != comm) {
        DBG(0, "removing command, name: %s\n", comm->name);
        if (NULL != comm->name)
            free(comm->name);
        if (UISH_CMDTYPE_USER == comm->type && NULL != comm->cmd.command) {
            DBG(0, "user command %s\n", comm->cmd.command);
            free(comm->cmd.command);
        }
        free(comm);
    }
}
