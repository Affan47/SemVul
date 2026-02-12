connection_ap_handle_onion(entry_connection_t *conn,
                           socks_request_t *socks,
                           origin_circuit_t *circ,
                           hostname_type_t addresstype)
{
  time_t now = approx_time();
  connection_t *base_conn = ENTRY_TO_CONN(conn);


  if (!conn->entry_cfg.onion_traffic) {
    log_warn(LD_APP, "Onion address %s requested from a port with .onion "
             "disabled", safe_str_client(socks->address));
    connection_mark_unattached_ap(conn, END_STREAM_REASON_ENTRYPOLICY);
    return -1;
  }


  if (SOCKS_COMMAND_IS_RESOLVE(socks->command)) {


    log_warn(LD_APP,
             "Resolve requests to hidden services not allowed. Failing.");
    connection_ap_handshake_socks_resolved(conn,RESOLVED_TYPE_ERROR,
                                           0,NULL,-1,TIME_MAX);
    connection_mark_unattached_ap(conn,
                               END_STREAM_REASON_SOCKSPROTOCOL |
                               END_STREAM_REASON_FLAG_ALREADY_SOCKS_REPLIED);
    return -1;
  }


  if (circ) {
    log_warn(LD_CONTROL, "Attachstream to a circuit is not "
             "supported for .onion addresses currently. Failing.");
    connection_mark_unattached_ap(conn, END_STREAM_REASON_TORPROTOCOL);
    return -1;
  }


  const char *onion_address = NULL;
  int rend_cache_lookup_result = -ENOENT;
  int descriptor_is_usable = 0;

  if (addresstype == ONION_V2_HOSTNAME) {
    rend_cache_entry_t *entry = NULL;


    rend_service_authorization_t *client_auth =
      rend_client_lookup_service_authorization(socks->address);

    const uint8_t *cookie = NULL;
    rend_auth_type_t auth_type = REND_NO_AUTH;
    if (client_auth) {
      log_info(LD_REND, "Using previously configured client authorization "
               "for hidden service request.");
      auth_type = client_auth->auth_type;
      cookie = client_auth->descriptor_cookie;
    }


    rend_data_t *rend_data = ENTRY_TO_EDGE_CONN(conn)->rend_data =
      rend_data_client_create(socks->address, NULL, (char *) cookie,
                              auth_type);
    if (rend_data == NULL) {
      return -1;
    }
    onion_address = rend_data_get_address(rend_data);
    log_info(LD_REND,"Got a hidden service request for ID '%s'",
             safe_str_client(onion_address));

    rend_cache_lookup_result = rend_cache_lookup_entry(onion_address,-1,
                                                       &entry);
    if (!rend_cache_lookup_result && entry) {
      descriptor_is_usable = rend_client_any_intro_points_usable(entry);
    }
  } else {
    tor_assert(addresstype == ONION_V3_HOSTNAME);
    const hs_descriptor_t *cached_desc = NULL;
    int retval;

    hs_ident_edge_conn_t *hs_conn_ident =
      tor_malloc_zero(sizeof(hs_ident_edge_conn_t));

    retval = hs_parse_address(socks->address, &hs_conn_ident->identity_pk,
                              NULL, NULL);
    if (retval < 0) {
      log_warn(LD_GENERAL, "failed to parse hs address");
      tor_free(hs_conn_ident);
      return -1;
    }
    ENTRY_TO_EDGE_CONN(conn)->hs_ident = hs_conn_ident;

    onion_address = socks->address;


    cached_desc = hs_cache_lookup_as_client(&hs_conn_ident->identity_pk);
    if (cached_desc) {
      rend_cache_lookup_result = 0;
      descriptor_is_usable =
        hs_client_any_intro_points_usable(&hs_conn_ident->identity_pk,
                                          cached_desc);
      log_info(LD_GENERAL, "Found %s descriptor in cache for %s. %s.",
               (descriptor_is_usable) ? "usable" : "unusable",
               safe_str_client(onion_address),
               (descriptor_is_usable) ? "Not fetching." : "Refetching.");
    } else {
      rend_cache_lookup_result = -ENOENT;
    }
  }


  unsigned int refetch_desc = 0;
  if (rend_cache_lookup_result < 0) {
    switch (-rend_cache_lookup_result) {
    case EINVAL:

      log_warn(LD_BUG,"Invalid service name '%s'",
               safe_str_client(onion_address));
      connection_mark_unattached_ap(conn, END_STREAM_REASON_TORPROTOCOL);
      return -1;
    case ENOENT:

      log_info(LD_REND, "No descriptor found in our cache for %s. Fetching.",
               safe_str_client(onion_address));
      refetch_desc = 1;
      break;
    default:
      log_warn(LD_BUG, "Unknown cache lookup error %d",
               rend_cache_lookup_result);
      return -1;
    }
  }


  rep_hist_note_used_internal(now, 0, 1);


  if (refetch_desc || !descriptor_is_usable) {
    edge_connection_t *edge_conn = ENTRY_TO_EDGE_CONN(conn);
    connection_ap_mark_as_non_pending_circuit(conn);
    base_conn->state = AP_CONN_STATE_RENDDESC_WAIT;
    if (addresstype == ONION_V2_HOSTNAME) {
      tor_assert(edge_conn->rend_data);
      rend_client_refetch_v2_renddesc(edge_conn->rend_data);

      return 0;
    } else {
      tor_assert(addresstype == ONION_V3_HOSTNAME);
      tor_assert(edge_conn->hs_ident);


      int ret = hs_client_refetch_hsdesc(&edge_conn->hs_ident->identity_pk);
      switch (ret) {
      case HS_CLIENT_FETCH_MISSING_INFO:


      case HS_CLIENT_FETCH_LAUNCHED:
      case HS_CLIENT_FETCH_PENDING:
      case HS_CLIENT_FETCH_HAVE_DESC:
        return 0;
      case HS_CLIENT_FETCH_ERROR:
      case HS_CLIENT_FETCH_NO_HSDIRS:
      case HS_CLIENT_FETCH_NOT_ALLOWED:

        return -1;
      }
    }
  }


  log_info(LD_REND, "Descriptor is here. Great.");

  base_conn->state = AP_CONN_STATE_CIRCUIT_WAIT;


  connection_ap_mark_as_pending_circuit(conn);
  return 0;
}
