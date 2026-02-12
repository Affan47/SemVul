connection_ap_handshake_rewrite_and_attach(entry_connection_t *conn,
                                           origin_circuit_t *circ,
                                           crypt_path_t *cpath)
{
  socks_request_t *socks = conn->socks_request;
  const or_options_t *options = get_options();
  connection_t *base_conn = ENTRY_TO_CONN(conn);
  time_t now = time(NULL);
  rewrite_result_t rr;


  memset(&rr, 0, sizeof(rr));
  connection_ap_handshake_rewrite(conn,&rr);

  if (rr.should_close) {


    connection_mark_unattached_ap(conn, rr.end_reason);
    if (END_STREAM_REASON_DONE == (rr.end_reason & END_STREAM_REASON_MASK))
      return 0;
    else
      return -1;
  }

  const time_t map_expires = rr.map_expires;
  const int automap = rr.automap;
  const addressmap_entry_source_t exit_source = rr.exit_source;


  hostname_type_t addresstype;
  if (!parse_extended_hostname(socks->address, &addresstype)) {
    control_event_client_status(LOG_WARN, "SOCKS_BAD_HOSTNAME HOSTNAME=%s",
                                escaped(socks->address));
    if (addresstype == BAD_HOSTNAME) {
      conn->socks_request->socks_extended_error_code = SOCKS5_HS_BAD_ADDRESS;
    }
    connection_mark_unattached_ap(conn, END_STREAM_REASON_TORPROTOCOL);
    return -1;
  }


  if (addresstype == EXIT_HOSTNAME) {


    routerset_t *excludeset = options->StrictNodes ?
      options->ExcludeExitNodesUnion_ : options->ExcludeExitNodes;
    const node_t *node = NULL;


    if (exit_source == ADDRMAPSRC_AUTOMAP) {


      log_warn(LD_APP,"Stale automapped address for '%s.exit'. Refusing.",
               safe_str_client(socks->address));
      control_event_client_status(LOG_WARN, "SOCKS_BAD_HOSTNAME HOSTNAME=%s",
                                  escaped(socks->address));
      connection_mark_unattached_ap(conn, END_STREAM_REASON_TORPROTOCOL);
      tor_assert_nonfatal_unreached();
      return -1;
    }


    if (exit_source == ADDRMAPSRC_DNS || exit_source == ADDRMAPSRC_NONE) {


      log_warn(LD_BUG,"Address '%s.exit', with impossible source for the "
               ".exit part. Refusing.",
               safe_str_client(socks->address));
      control_event_client_status(LOG_WARN, "SOCKS_BAD_HOSTNAME HOSTNAME=%s",
                                  escaped(socks->address));
      connection_mark_unattached_ap(conn, END_STREAM_REASON_TORPROTOCOL);
      return -1;
    }

    tor_assert(!automap);


    char *s = strrchr(socks->address,'.');
    if (s) {

      if (s[1] != '\0') {

        conn->chosen_exit_name = tor_strdup(s+1);
        node = node_get_by_nickname(conn->chosen_exit_name, 0);

        if (exit_source == ADDRMAPSRC_TRACKEXIT) {

          conn->chosen_exit_retries = TRACKHOSTEXITS_RETRIES;
        }
        *s = 0;
      } else {

        log_warn(LD_APP,"Malformed exit address '%s.exit'. Refusing.",
                 safe_str_client(socks->address));
        control_event_client_status(LOG_WARN, "SOCKS_BAD_HOSTNAME HOSTNAME=%s",
                                    escaped(socks->address));
        connection_mark_unattached_ap(conn, END_STREAM_REASON_TORPROTOCOL);
        return -1;
      }
    } else {


      conn->chosen_exit_name = tor_strdup(socks->address);
      node = node_get_by_nickname(conn->chosen_exit_name, 0);
      if (node) {
        *socks->address = 0;
        node_get_address_string(node, socks->address, sizeof(socks->address));
      }
    }


    if (!node) {
      log_warn(LD_APP,
               "Unrecognized relay in exit address '%s.exit'. Refusing.",
               safe_str_client(socks->address));
      connection_mark_unattached_ap(conn, END_STREAM_REASON_TORPROTOCOL);
      return -1;
    }

    if (routerset_contains_node(excludeset, node)) {
      log_warn(LD_APP,
               "Excluded relay in exit address '%s.exit'. Refusing.",
               safe_str_client(socks->address));
      connection_mark_unattached_ap(conn, END_STREAM_REASON_TORPROTOCOL);
      return -1;
    }


  }


  if (addresstype != ONION_V3_HOSTNAME && addresstype != ONION_V2_HOSTNAME) {


    if (address_is_invalid_destination(socks->address, 1)) {
      control_event_client_status(LOG_WARN, "SOCKS_BAD_HOSTNAME HOSTNAME=%s",
                                  escaped(socks->address));
      log_warn(LD_APP,
               "Destination '%s' seems to be an invalid hostname. Failing.",
               safe_str_client(socks->address));
      connection_mark_unattached_ap(conn, END_STREAM_REASON_TORPROTOCOL);
      return -1;
    }


    if (!conn->entry_cfg.dns_request && !conn->entry_cfg.ipv4_traffic
        && !conn->entry_cfg.ipv6_traffic) {
        log_warn(LD_APP, "Refusing to connect to non-hidden-service hostname "
                 "or IP address %s because Port has OnionTrafficOnly set (or "
                 "NoDNSRequest, NoIPv4Traffic, and NoIPv6Traffic).",
                 safe_str_client(socks->address));
        connection_mark_unattached_ap(conn, END_STREAM_REASON_ENTRYPOLICY);
        return -1;
    }


    tor_addr_t dummy_addr;
    int socks_family = tor_addr_parse(&dummy_addr, socks->address);

    if (socks_family == -1) {
      if (!conn->entry_cfg.dns_request) {
        log_warn(LD_APP, "Refusing to connect to hostname %s "
                 "because Port has NoDNSRequest set.",
                 safe_str_client(socks->address));
        connection_mark_unattached_ap(conn, END_STREAM_REASON_ENTRYPOLICY);
        return -1;
      }
    } else if (socks_family == AF_INET) {
      if (!conn->entry_cfg.ipv4_traffic) {
        log_warn(LD_APP, "Refusing to connect to IPv4 address %s because "
                 "Port has NoIPv4Traffic set.",
                 safe_str_client(socks->address));
        connection_mark_unattached_ap(conn, END_STREAM_REASON_ENTRYPOLICY);
        return -1;
      }
    } else if (socks_family == AF_INET6) {
      if (!conn->entry_cfg.ipv6_traffic) {
        log_warn(LD_APP, "Refusing to connect to IPv6 address %s because "
                 "Port has NoIPv6Traffic set.",
                 safe_str_client(socks->address));
        connection_mark_unattached_ap(conn, END_STREAM_REASON_ENTRYPOLICY);
        return -1;
      }
    } else {
      tor_assert_nonfatal_unreached_once();
    }


    if (socks->command == SOCKS_COMMAND_RESOLVE) {
      tor_addr_t answer;

      if (tor_addr_parse(&answer, socks->address) >= 0) {

        strlcpy(socks->address, rr.orig_address, sizeof(socks->address));
        connection_ap_handshake_socks_resolved_addr(conn, &answer, -1,
                                                    map_expires);
        connection_mark_unattached_ap(conn,
                                END_STREAM_REASON_DONE |
                                END_STREAM_REASON_FLAG_ALREADY_SOCKS_REPLIED);
        return 0;
      }
      tor_assert(!automap);
      rep_hist_note_used_resolve(now);
    } else if (socks->command == SOCKS_COMMAND_CONNECT) {


      tor_assert(!automap);

      if (socks->port == 0) {
        log_notice(LD_APP,"Application asked to connect to port 0. Refusing.");
        connection_mark_unattached_ap(conn, END_STREAM_REASON_TORPROTOCOL);
        return -1;
      }


      if (options->ClientRejectInternalAddresses &&
          !conn->use_begindir && !conn->chosen_exit_name && !circ) {


        tor_addr_t addr;
        if (tor_addr_hostname_is_local(socks->address) ||
            (tor_addr_parse(&addr, socks->address) >= 0 &&
             tor_addr_is_internal(&addr, 0))) {


          if (conn->is_transparent_ap) {
#define WARN_INTRVL_LOOP 300
            static ratelim_t loop_warn_limit = RATELIM_INIT(WARN_INTRVL_LOOP);
            char *m;
            if ((m = rate_limit_log(&loop_warn_limit, approx_time()))) {
              log_warn(LD_NET,
                       "Rejecting request for anonymous connection to private "
                       "address %s on a TransPort or NATDPort.  Possible loop "
                       "in your NAT rules?%s", safe_str_client(socks->address),
                       m);
              tor_free(m);
            }
          } else {
#define WARN_INTRVL_PRIV 300
            static ratelim_t priv_warn_limit = RATELIM_INIT(WARN_INTRVL_PRIV);
            char *m;
            if ((m = rate_limit_log(&priv_warn_limit, approx_time()))) {
              log_warn(LD_NET,
                       "Rejecting SOCKS request for anonymous connection to "
                       "private address %s.%s",
                       safe_str_client(socks->address),m);
              tor_free(m);
            }
          }
          connection_mark_unattached_ap(conn, END_STREAM_REASON_PRIVATE_ADDR);
          return -1;
        }
      }


      {
        tor_addr_t addr;

        if (tor_addr_parse(&addr, socks->address) >= 0) {

          sa_family_t family = tor_addr_family(&addr);

          if ((family == AF_INET && ! conn->entry_cfg.ipv4_traffic) ||
              (family == AF_INET6 && ! conn->entry_cfg.ipv6_traffic)) {


            log_warn(LD_NET, "Rejecting SOCKS request for an IP address "
                     "family that this listener does not support.");
            connection_mark_unattached_ap(conn, END_STREAM_REASON_ENTRYPOLICY);
            return -1;
          } else if (family == AF_INET6 && socks->socks_version == 4) {


            log_warn(LD_NET, "Rejecting SOCKS4 request for an IPv6 address.");
            connection_mark_unattached_ap(conn, END_STREAM_REASON_ENTRYPOLICY);
            return -1;
          } else if (socks->socks_version == 4 &&
                     !conn->entry_cfg.ipv4_traffic) {


            log_warn(LD_NET, "Rejecting SOCKS4 request on a listener with "
                     "no IPv4 traffic supported.");
            connection_mark_unattached_ap(conn, END_STREAM_REASON_ENTRYPOLICY);
            return -1;
          } else if (family == AF_INET6) {


            conn->entry_cfg.ipv4_traffic = 0;
          } else if (family == AF_INET) {


            conn->entry_cfg.ipv6_traffic = 0;
          }


          if (!network_reentry_is_allowed() &&
              nodelist_reentry_contains(&addr, socks->port)) {
            log_warn(LD_APP, "Not attempting connection to %s:%d because "
                     "the network would reject it. Are you trying to send "
                     "Tor traffic over Tor? This traffic can be harmful to "
                     "the Tor network. If you really need it, try using "
                     "a bridge as a workaround.",
                     safe_str_client(socks->address), socks->port);
            connection_mark_unattached_ap(conn, END_STREAM_REASON_TORPROTOCOL);
            return -1;
          }
        }
      }


      if (socks->socks_version == 4)
        conn->entry_cfg.ipv6_traffic = 0;


      if (!conn->use_begindir && !conn->chosen_exit_name && !circ) {

        const node_t *r =
          router_find_exact_exit_enclave(socks->address, socks->port);
        if (r) {
          log_info(LD_APP,
                   "Redirecting address %s to exit at enclave router %s",
                   safe_str_client(socks->address), node_describe(r));


          conn->chosen_exit_name =
            tor_strdup(hex_str(r->identity, DIGEST_LEN));
          conn->chosen_exit_optional = 1;
        }
      }


      if (!conn->use_begindir && !conn->chosen_exit_name && !circ)
        if (consider_plaintext_ports(conn, socks->port) < 0)
          return -1;


      if (!conn->use_begindir) {

        rep_hist_note_used_port(now, socks->port);
      }
    } else if (socks->command == SOCKS_COMMAND_RESOLVE_PTR) {
      rep_hist_note_used_resolve(now);

    } else {

      tor_fragile_assert();
    }


    base_conn->state = AP_CONN_STATE_CIRCUIT_WAIT;


    int rv;
    if (circ) {
      rv = connection_ap_handshake_attach_chosen_circuit(conn, circ, cpath);
    } else {


      connection_ap_mark_as_pending_circuit(conn);
      rv = 0;
    }


    if (rv < 0) {
      if (!base_conn->marked_for_close)
        connection_mark_unattached_ap(conn, END_STREAM_REASON_CANT_ATTACH);
      return -1;
    }

    return 0;
  } else {


    if (addresstype == ONION_V2_HOSTNAME) {
      static bool log_once = false;
      if (!log_once) {
        log_warn(LD_PROTOCOL, "Tried to connect to a v2 onion address, but "
                 "this version of Tor no longer supports them. Please "
                 "encourage the site operator to upgrade. For more "
                 "information see "
                 "https://blog.torproject.org/v2-deprecation-timeline.");
        log_once = true;
      }
      control_event_client_status(LOG_WARN, "SOCKS_BAD_HOSTNAME HOSTNAME=%s",
                                  escaped(socks->address));


      conn->socks_request->socks_extended_error_code = SOCKS5_HS_BAD_ADDRESS;
      connection_mark_unattached_ap(conn, END_STREAM_REASON_TORPROTOCOL);
      return -1;
    }

    tor_assert(addresstype == ONION_V3_HOSTNAME);
    tor_assert(!automap);
    return connection_ap_handle_onion(conn, socks, circ);
  }

  return 0;
}
