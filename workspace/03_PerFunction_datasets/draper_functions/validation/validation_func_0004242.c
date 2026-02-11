tgdb_client_create_context(const char
        *debugger_path, int argc, char **argv, const char *config_dir,
        enum tgdb_client_supported_debuggers debugger,
        enum tgdb_client_supported_protocols protocol, struct logger *logger)
{

    struct tgdb_client_context *tcc = NULL;


    if (debugger == TGDB_CLIENT_DEBUGGER_GNU_GDB &&
            (protocol == TGDB_CLIENT_PROTOCOL_GNU_GDB_ANNOTATE_TWO ||
                    protocol == TGDB_CLIENT_PROTOCOL_GNU_GDB_GDBMI)
            ) {

        tcc = (struct tgdb_client_context *)
                cgdb_malloc(sizeof (struct tgdb_client_context));
        tcc->debugger = debugger;
        tcc->protocol = protocol;
        tcc->logger = logger;

        if (protocol == TGDB_CLIENT_PROTOCOL_GNU_GDB_ANNOTATE_TWO)
            tcc->tgdb_client_interface = &tgdb_client_debugger_interfaces[0];
        else if (protocol == TGDB_CLIENT_PROTOCOL_GNU_GDB_GDBMI)
            tcc->tgdb_client_interface = &tgdb_client_debugger_interfaces[1];

        tcc->tgdb_debugger_context =
                tcc->tgdb_client_interface->
                tgdb_client_create_context(debugger_path, argc, argv,
                config_dir, logger);

        if (tcc->tgdb_debugger_context == NULL) {
            free(tcc);
            logger_write_pos(tcc->logger, __FILE__, __LINE__,
                    "a2_create_instance failed");
            return NULL;
        }
    } else {
        logger_write_pos(tcc->logger, __FILE__, __LINE__,
                "tgdb_client_create_context protocol not recognized");
    }

    return tcc;
}
