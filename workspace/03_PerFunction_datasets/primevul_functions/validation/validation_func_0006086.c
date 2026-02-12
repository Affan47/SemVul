multi_connection_established(struct multi_context *m, struct multi_instance *mi)
{
    if (tls_authentication_status(mi->context.c2.tls_multi, 0) == TLS_AUTHENTICATION_SUCCEEDED)
    {
        struct gc_arena gc = gc_new();
        unsigned int option_types_found = 0;

        const unsigned int option_permissions_mask =
            OPT_P_INSTANCE
            | OPT_P_INHERIT
            | OPT_P_PUSH
            | OPT_P_TIMER
            | OPT_P_CONFIG
            | OPT_P_ECHO
            | OPT_P_COMP
            | OPT_P_SOCKFLAGS;

        int cc_succeeded = true;
        int cc_succeeded_count = 0;

        ASSERT(mi->context.c1.tuntap);


        tls_lock_common_name(mi->context.c2.tls_multi);
        tls_lock_cert_hash_set(mi->context.c2.tls_multi);


        generate_prefix(mi);


        if (!mi->context.options.duplicate_cn)
        {
            multi_delete_dup(m, mi);
        }


        mi->vaddr_handle = -1;


        if (mi->context.options.client_config_dir)
        {
            const char *ccd_file;

            ccd_file = platform_gen_path(mi->context.options.client_config_dir,
                                         tls_common_name(mi->context.c2.tls_multi,
                                                         false),
                                         &gc);


            if (platform_test_file(ccd_file))
            {
                options_server_import(&mi->context.options,
                                      ccd_file,
                                      D_IMPORT_ERRORS|M_OPTERR,
                                      option_permissions_mask,
                                      &option_types_found,
                                      mi->context.c2.es);
            }
            else
            {
                ccd_file = platform_gen_path(mi->context.options.client_config_dir,
                                             CCD_DEFAULT,
                                             &gc);

                if (platform_test_file(ccd_file))
                {
                    options_server_import(&mi->context.options,
                                          ccd_file,
                                          D_IMPORT_ERRORS|M_OPTERR,
                                          option_permissions_mask,
                                          &option_types_found,
                                          mi->context.c2.es);
                }
            }
        }


        multi_select_virtual_addr(m, mi);


        multi_client_connect_setenv(m, mi);

#ifdef ENABLE_PLUGIN


        if (plugin_defined(mi->context.plugins, OPENVPN_PLUGIN_CLIENT_CONNECT))
        {
            struct argv argv = argv_new();
            const char *dc_file = platform_create_temp_file(mi->context.options.tmp_dir,
                                                            "cc", &gc);

            if (!dc_file)
            {
                cc_succeeded = false;
                goto script_depr_failed;
            }

            argv_printf(&argv, "%s", dc_file);
            if (plugin_call(mi->context.plugins, OPENVPN_PLUGIN_CLIENT_CONNECT, &argv, NULL, mi->context.c2.es) != OPENVPN_PLUGIN_FUNC_SUCCESS)
            {
                msg(M_WARN, "WARNING: client-connect plugin call failed");
                cc_succeeded = false;
            }
            else
            {
                multi_client_connect_post(m, mi, dc_file, option_permissions_mask, &option_types_found);
                ++cc_succeeded_count;
            }

            if (!platform_unlink(dc_file))
            {
                msg(D_MULTI_ERRORS, "MULTI: problem deleting temporary file: %s",
                    dc_file);
            }

script_depr_failed:
            argv_free(&argv);
        }


        if (plugin_defined(mi->context.plugins, OPENVPN_PLUGIN_CLIENT_CONNECT_V2))
        {
            struct plugin_return pr;

            plugin_return_init(&pr);

            if (plugin_call(mi->context.plugins, OPENVPN_PLUGIN_CLIENT_CONNECT_V2, NULL, &pr, mi->context.c2.es) != OPENVPN_PLUGIN_FUNC_SUCCESS)
            {
                msg(M_WARN, "WARNING: client-connect-v2 plugin call failed");
                cc_succeeded = false;
            }
            else
            {
                multi_client_connect_post_plugin(m, mi, &pr, option_permissions_mask, &option_types_found);
                ++cc_succeeded_count;
            }

            plugin_return_free(&pr);
        }
#endif


        if (mi->context.options.client_connect_script && cc_succeeded)
        {
            struct argv argv = argv_new();
            const char *dc_file = NULL;

            setenv_str(mi->context.c2.es, "script_type", "client-connect");

            dc_file = platform_create_temp_file(mi->context.options.tmp_dir,
                                                "cc", &gc);
            if (!dc_file)
            {
                cc_succeeded = false;
                goto script_failed;
            }

            argv_parse_cmd(&argv, mi->context.options.client_connect_script);
            argv_printf_cat(&argv, "%s", dc_file);

            if (openvpn_run_script(&argv, mi->context.c2.es, 0, "--client-connect"))
            {
                multi_client_connect_post(m, mi, dc_file, option_permissions_mask, &option_types_found);
                ++cc_succeeded_count;
            }
            else
            {
                cc_succeeded = false;
            }

            if (!platform_unlink(dc_file))
            {
                msg(D_MULTI_ERRORS, "MULTI: problem deleting temporary file: %s",
                    dc_file);
            }

script_failed:
            argv_free(&argv);
        }


#ifdef MANAGEMENT_DEF_AUTH
        if (cc_succeeded && mi->cc_config)
        {
            multi_client_connect_mda(m, mi, mi->cc_config, option_permissions_mask, &option_types_found);
            ++cc_succeeded_count;
        }
#endif


        if (mi->context.options.disable)
        {
            msg(D_MULTI_ERRORS, "MULTI: client has been rejected due to 'disable' directive");
            cc_succeeded = false;
            cc_succeeded_count = 0;
        }

        if (cc_succeeded)
        {


            do_deferred_options(&mi->context, option_types_found);


            if (!mi->context.c2.push_ifconfig_defined)
            {
                msg(D_MULTI_ERRORS, "MULTI: no dynamic or static remote --ifconfig address is available for %s",
                    multi_instance_string(mi, false, &gc));
            }


            if (!ifconfig_push_constraint_satisfied(&mi->context))
            {

                msg(D_MULTI_ERRORS, "MULTI ERROR: primary virtual IP for %s (%s) violates tunnel network/netmask constraint (%s/%s)",
                    multi_instance_string(mi, false, &gc),
                    print_in_addr_t(mi->context.c2.push_ifconfig_local, 0, &gc),
                    print_in_addr_t(mi->context.options.push_ifconfig_constraint_network, 0, &gc),
                    print_in_addr_t(mi->context.options.push_ifconfig_constraint_netmask, 0, &gc));
            }


            if (TUNNEL_TYPE(mi->context.c1.tuntap) == DEV_TYPE_TUN)
            {
                if (mi->context.c2.push_ifconfig_defined)
                {
                    multi_learn_in_addr_t(m, mi, mi->context.c2.push_ifconfig_local, -1, true);
                    msg(D_MULTI_LOW, "MULTI: primary virtual IP for %s: %s",
                        multi_instance_string(mi, false, &gc),
                        print_in_addr_t(mi->context.c2.push_ifconfig_local, 0, &gc));
                }

                if (mi->context.c2.push_ifconfig_ipv6_defined)
                {
                    multi_learn_in6_addr(m, mi, mi->context.c2.push_ifconfig_ipv6_local, -1, true);

                    msg(D_MULTI_LOW, "MULTI: primary virtual IPv6 for %s: %s",
                        multi_instance_string(mi, false, &gc),
                        print_in6_addr(mi->context.c2.push_ifconfig_ipv6_local, 0, &gc));
                }


                multi_add_iroutes(m, mi);


                remove_iroutes_from_push_route_list(&mi->context.options);
            }
            else if (mi->context.options.iroutes)
            {
                msg(D_MULTI_ERRORS, "MULTI: --iroute options rejected for %s -- iroute only works with tun-style tunnels",
                    multi_instance_string(mi, false, &gc));
            }


            mi->reporting_addr = mi->context.c2.push_ifconfig_local;
            mi->reporting_addr_ipv6 = mi->context.c2.push_ifconfig_ipv6_local;


            mi->context.c2.context_auth = CAS_SUCCEEDED;

#ifdef ENABLE_ASYNC_PUSH

            if (mi->context.c2.push_request_received)
            {
                process_incoming_push_request(&mi->context);
            }
#endif
        }
        else
        {

            mi->context.c2.context_auth = cc_succeeded_count ? CAS_PARTIAL : CAS_FAILED;
        }


        mi->connection_established_flag = true;


        ++m->n_clients;
        update_mstat_n_clients(m->n_clients);
        --mi->n_clients_delta;

#ifdef MANAGEMENT_DEF_AUTH
        if (management)
        {
            management_connection_established(management, &mi->context.c2.mda_context, mi->context.c2.es);
        }
#endif

        gc_free(&gc);
    }


    mi->context.c2.push_reply_deferred = false;
}
