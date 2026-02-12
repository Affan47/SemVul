if (request_reply(&request, &reply, RPY_CLIENT_ACCESSES, 0)) {
          n_replies = ntohl(reply.data.client_accesses.n_clients);
          for (j=0; j<n_replies; j++) {
            ip = ntohl(reply.data.client_accesses.clients[j].ip);
            if (ip != 0UL) {


              client_hits = ntohl(reply.data.client_accesses.clients[j].client_hits);
              peer_hits = ntohl(reply.data.client_accesses.clients[j].peer_hits);
              cmd_hits_auth = ntohl(reply.data.client_accesses.clients[j].cmd_hits_auth);
              cmd_hits_normal = ntohl(reply.data.client_accesses.clients[j].cmd_hits_normal);
              cmd_hits_bad = ntohl(reply.data.client_accesses.clients[j].cmd_hits_bad);
              last_ntp_hit_ago = ntohl(reply.data.client_accesses.clients[j].last_ntp_hit_ago);
              last_cmd_hit_ago = ntohl(reply.data.client_accesses.clients[j].last_cmd_hit_ago);

              if (no_dns) {
                snprintf(hostname_buf, sizeof(hostname_buf),
                         "%s", UTI_IPToDottedQuad(ip));
              } else {
                DNS_IPAddress2Name(ip, hostname_buf, sizeof(hostname_buf));
                hostname_buf[25] = 0;
              }
              printf("%-25s  %6d  %6d  %6d  %6d  %6d  ",
                     hostname_buf,
                     client_hits, peer_hits,
                     cmd_hits_auth, cmd_hits_normal, cmd_hits_bad);
              print_seconds(last_ntp_hit_ago);
              printf("  ");
              print_seconds(last_cmd_hit_ago);
              printf("\n");
            }
          }


          for (i=0; i<clients_looked_up; i++) {
            todo = todo->next;
          }

    }
