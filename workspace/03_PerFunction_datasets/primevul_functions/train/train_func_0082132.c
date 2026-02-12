ConnectionExists(struct SessionHandle *data,
                 struct connectdata *needle,
                 struct connectdata **usethis,
                 bool *force_reuse)
{
  struct connectdata *check;
  struct connectdata *chosen = 0;
  bool canPipeline = IsPipeliningPossible(data, needle);
  bool wantNTLMhttp = ((data->state.authhost.want & CURLAUTH_NTLM) ||
                       (data->state.authhost.want & CURLAUTH_NTLM_WB)) &&
    (needle->handler->protocol & PROTO_FAMILY_HTTP) ? TRUE : FALSE;
  struct connectbundle *bundle;

  *force_reuse = FALSE;


  if(canPipeline && Curl_pipeline_site_blacklisted(data, needle)) {
    canPipeline = FALSE;
  }


  bundle = Curl_conncache_find_bundle(needle, data->state.conn_cache);
  if(bundle) {
    size_t max_pipe_len = Curl_multi_max_pipeline_length(data->multi);
    size_t best_pipe_len = max_pipe_len;
    struct curl_llist_element *curr;

    infof(data, "Found bundle for host %s: %p\n",
          needle->host.name, (void *)bundle);


    if(canPipeline && !bundle->server_supports_pipelining) {
      infof(data, "Server doesn't support pipelining\n");
      canPipeline = FALSE;
    }

    curr = bundle->conn_list->head;
    while(curr) {
      bool match = FALSE;
#if defined(USE_NTLM)
      bool credentialsMatch = FALSE;
#endif
      size_t pipeLen;


      check = curr->ptr;
      curr = curr->next;

      if(disconnect_if_dead(check, data))
        continue;

      pipeLen = check->send_pipe->size + check->recv_pipe->size;

      if(canPipeline) {

        struct SessionHandle* sh = gethandleathead(check->send_pipe);
        struct SessionHandle* rh = gethandleathead(check->recv_pipe);
        if(sh) {
          if(!IsPipeliningPossible(sh, check))
            continue;
        }
        else if(rh) {
          if(!IsPipeliningPossible(rh, check))
            continue;
        }
      }
      else {
        if(pipeLen > 0) {


          continue;
        }

        if(Curl_resolver_asynch()) {


          if(!check->ip_addr_str[0]) {
            infof(data,
                  "Connection #%ld is still name resolving, can't reuse\n",
                  check->connection_id);
            continue;
          }
        }

        if((check->sock[FIRSTSOCKET] == CURL_SOCKET_BAD) ||
           check->bits.close) {


          infof(data, "Connection #%ld isn't open enough, can't reuse\n",
                check->connection_id);
#ifdef DEBUGBUILD
          if(check->recv_pipe->size > 0) {
            infof(data,
                  "BAD! Unconnected #%ld has a non-empty recv pipeline!\n",
                  check->connection_id);
          }
#endif
          continue;
        }
      }

      if((needle->handler->flags&PROTOPT_SSL) !=
         (check->handler->flags&PROTOPT_SSL))

        if(!(needle->handler->protocol & check->handler->protocol))

          continue;

      if(needle->handler->flags&PROTOPT_SSL) {
        if((data->set.ssl.verifypeer != check->verifypeer) ||
           (data->set.ssl.verifyhost != check->verifyhost))
          continue;
      }

      if(needle->bits.proxy != check->bits.proxy)

        continue;

      if(!canPipeline && check->inuse)


        continue;

      if(needle->localdev || needle->localport) {


        if((check->localport != needle->localport) ||
           (check->localportrange != needle->localportrange) ||
           !check->localdev ||
           !needle->localdev ||
           strcmp(check->localdev, needle->localdev))
          continue;
      }

      if((!(needle->handler->flags & PROTOPT_CREDSPERREQUEST)) ||
         wantNTLMhttp) {


        if(!strequal(needle->user, check->user) ||
           !strequal(needle->passwd, check->passwd)) {

          continue;
        }
#if defined(USE_NTLM)
        credentialsMatch = TRUE;
#endif
      }

      if(!needle->bits.httpproxy || needle->handler->flags&PROTOPT_SSL ||
         (needle->bits.httpproxy && check->bits.httpproxy &&
          needle->bits.tunnel_proxy && check->bits.tunnel_proxy &&
          Curl_raw_equal(needle->proxy.name, check->proxy.name) &&
          (needle->port == check->port))) {


        if((Curl_raw_equal(needle->handler->scheme, check->handler->scheme) ||
            needle->handler->protocol & check->handler->protocol) &&
           Curl_raw_equal(needle->host.name, check->host.name) &&
           needle->remote_port == check->remote_port) {
          if(needle->handler->flags & PROTOPT_SSL) {


            if(!Curl_ssl_config_matches(&needle->ssl_config,
                                        &check->ssl_config)) {
              DEBUGF(infof(data,
                           "Connection #%ld has different SSL parameters, "
                           "can't reuse\n",
                           check->connection_id));
              continue;
            }
            else if(check->ssl[FIRSTSOCKET].state != ssl_connection_complete) {
              DEBUGF(infof(data,
                           "Connection #%ld has not started SSL connect, "
                           "can't reuse\n",
                           check->connection_id));
              continue;
            }
          }
          match = TRUE;
        }
      }
      else {

        if(check->bits.proxy &&
           (needle->proxytype == check->proxytype) &&
           (needle->bits.tunnel_proxy == check->bits.tunnel_proxy) &&
           Curl_raw_equal(needle->proxy.name, check->proxy.name) &&
           needle->port == check->port) {

          match = TRUE;
        }
      }

      if(match) {
#if defined(USE_NTLM)


        if(wantNTLMhttp) {
          if(credentialsMatch && check->ntlm.state != NTLMSTATE_NONE) {
            chosen = check;


            *force_reuse = TRUE;
            break;
          }
          else if(credentialsMatch)

            chosen = check;
          continue;
        }
#endif

        if(canPipeline) {


          if(pipeLen == 0) {

            chosen = check;
            break;
          }


          if(pipeLen >= max_pipe_len)
            continue;


          if(Curl_pipeline_penalized(data, check))
            continue;

          if(pipeLen < best_pipe_len) {


            chosen = check;
            best_pipe_len = pipeLen;
            continue;
          }
        }
        else {

          chosen = check;
          break;
        }
      }
    }
  }

  if(chosen) {
    *usethis = chosen;
    return TRUE;
  }

  return FALSE;
}
