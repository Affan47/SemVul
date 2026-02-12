multi_client_connect_mda(struct multi_context *m,
                         struct multi_instance *mi,
                         const struct buffer_list *config,
                         unsigned int option_permissions_mask,
                         unsigned int *option_types_found)
{
    if (config)
    {
        struct buffer_entry *be;

        for (be = config->head; be != NULL; be = be->next)
        {
            const char *opt = BSTR(&be->buf);
            options_string_import(&mi->context.options,
                                  opt,
                                  D_IMPORT_ERRORS|M_OPTERR,
                                  option_permissions_mask,
                                  option_types_found,
                                  mi->context.c2.es);
        }


        multi_select_virtual_addr(m, mi);
        multi_set_virtual_addr_env(mi);
    }
}
