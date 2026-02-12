submit_request(CMD_Request *request, CMD_Reply *reply, int *reply_auth_ok)
{
  unsigned long tx_sequence;
  socklen_t where_from_len;
  union sockaddr_in46 where_from;
  int bad_length, bad_sender, bad_sequence, bad_header;
  int select_status;
  int recvfrom_status;
  int read_length;
  int expected_length;
  int command_length;
  int auth_length;
  struct timeval tv;
  int timeout;
  int n_attempts;
  fd_set rdfd, wrfd, exfd;

  request->version = PROTO_VERSION_NUMBER;
  request->pkt_type = PKT_TYPE_CMD_REQUEST;
  request->res1 = 0;
  request->res2 = 0;
  tx_sequence = sequence++;
  request->sequence = htonl(tx_sequence);
  request->attempt = 0;
  request->utoken = htonl(utoken);
  request->token = htonl(token);

  timeout = initial_timeout;

  n_attempts = 0;

  do {


    if (password) {
      if (!utoken || (request->command == htons(REQ_LOGON))) {


        request->utoken = htonl(SPECIAL_UTOKEN);
      }
      auth_length = generate_auth(request);
    } else {
      auth_length = 0;
    }

    command_length = PKL_CommandLength(request);
    assert(command_length > 0);


    if (!auth_length) {
      memset(((char *)request) + command_length, 0, 16);
      auth_length = 16;
    }

#if 0
    printf("Sent command length=%d bytes auth length=%d bytes\n", command_length, auth_length);
#endif

    if (sendto(sock_fd, (void *) request, command_length + auth_length, 0,
               &his_addr.u, his_addr_len) < 0) {


#if 0
      perror("Could not send packet");
#endif
      return 0;
    }


    ++ request->attempt;

    tv.tv_sec = timeout / 1000;
    tv.tv_usec = timeout % 1000 * 1000;
    timeout *= 2;

    FD_ZERO(&rdfd);
    FD_ZERO(&wrfd);
    FD_ZERO(&exfd);

    FD_SET(sock_fd, &rdfd);

    select_status = select(sock_fd + 1, &rdfd, &wrfd, &exfd, &tv);

    if (select_status < 0) {
#if 0
      perror("Select returned negative status");
#endif
    } else if (select_status == 0) {

      n_attempts ++;
      if (n_attempts > max_retries) {
        return 0;
      }


      continue;

    } else {

      where_from_len = sizeof(where_from);
      recvfrom_status = recvfrom(sock_fd, (void *) reply, sizeof(CMD_Reply), 0,
                                 &where_from.u, &where_from_len);


#if 0
      printf("Received packet, status=%d\n", recvfrom_status);
#endif

      if (recvfrom_status < 0) {


        n_attempts++;
        if (n_attempts > max_retries) {
          return 0;
        }
      } else {

        read_length = recvfrom_status;
        expected_length = PKL_ReplyLength(reply);

        bad_length = (read_length < expected_length ||
                      expected_length < offsetof(CMD_Reply, data));
        bad_sender = (where_from.u.sa_family != his_addr.u.sa_family ||
                      (where_from.u.sa_family == AF_INET &&
                       (where_from.in4.sin_addr.s_addr != his_addr.in4.sin_addr.s_addr ||
                        where_from.in4.sin_port != his_addr.in4.sin_port)) ||
#ifdef HAVE_IPV6
                      (where_from.u.sa_family == AF_INET6 &&
                       (memcmp(where_from.in6.sin6_addr.s6_addr, his_addr.in6.sin6_addr.s6_addr,
                               sizeof (where_from.in6.sin6_addr.s6_addr)) != 0 ||
                        where_from.in6.sin6_port != his_addr.in6.sin6_port)) ||
#endif
                      0);

        if (!bad_length) {
          bad_sequence = (ntohl(reply->sequence) != tx_sequence);
        } else {
          bad_sequence = 0;
        }

        if (bad_length || bad_sender || bad_sequence) {
          n_attempts++;
          if (n_attempts > max_retries) {
            return 0;
          }
          continue;
        }

        bad_header = ((reply->version != PROTO_VERSION_NUMBER &&
                       !(reply->version >= PROTO_VERSION_MISMATCH_COMPAT &&
                         ntohs(reply->status) == STT_BADPKTVERSION)) ||
                      (reply->pkt_type != PKT_TYPE_CMD_REPLY) ||
                      (reply->res1 != 0) ||
                      (reply->res2 != 0) ||
                      (reply->command != request->command));

        if (bad_header) {
          n_attempts++;
          if (n_attempts > max_retries) {
            return 0;
          }
          continue;
        }


#if 0
        printf("Reply cmd=%d reply=%d stat=%d num=%d tot=%d seq=%d utok=%08lx tok=%d\n",
               ntohs(reply->command), ntohs(reply->reply),
               ntohs(reply->status), ntohs(reply->number),
               ntohs(reply->total),
               ntohl(reply->sequence),
               ntohl(reply->utoken),
               ntohl(reply->token));
#endif

        if (password) {
          *reply_auth_ok = check_reply_auth(reply, read_length);
        } else {


          *reply_auth_ok = 1;
        }

        utoken = ntohl(reply->utoken);

        if (*reply_auth_ok) {


          utoken = ntohl(reply->utoken);
          token = ntohl(reply->token);
        }

        break;

      }
    }
  } while (1);

  return 1;
}
