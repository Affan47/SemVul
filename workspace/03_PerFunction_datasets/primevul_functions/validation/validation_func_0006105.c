multi_client_connect_post(struct multi_context *m,
                          struct multi_instance *mi,
                          const char *dc_file,
                          unsigned int option_permissions_mask,
                          unsigned int *option_types_found)
{

    if (platform_test_file(dc_file))
    {
        options_server_import(&mi->context.options,
                              dc_file,
                              D_IMPORT_ERRORS|M_OPTERR,
                              option_permissions_mask,
                              option_types_found,
                              mi->context.c2.es);


        multi_select_virtual_addr(m, mi);
        multi_set_virtual_addr_env(mi);
    }
}
