sshv2_connect (gftp_request * request)
{
  struct servent serv_struct;
  sshv2_params * params;
  sshv2_message message;
  int ret, fdm, ptymfd;
  guint32 version;
  char **args;
  pid_t child;

  g_return_val_if_fail (request != NULL, GFTP_EFATAL);
  g_return_val_if_fail (request->protonum == GFTP_SSHV2_NUM, GFTP_EFATAL);
  g_return_val_if_fail (request->hostname != NULL, GFTP_EFATAL);

  if (request->datafd > 0)
    return (0);

  params = request->protocol_data;

  request->logging_function (gftp_logging_misc, request,
			     _("Opening SSH connection to %s\n"),
                             request->hostname);

  if (request->port == 0)
    {
      if (!r_getservbyname ("ssh", "tcp", &serv_struct, NULL))
        {
         request->logging_function (gftp_logging_error, request,
                                    _("Cannot look up service name %s/tcp. Please check your services file\n"),
                                    "ssh");
        }
      else
        request->port = ntohs (serv_struct.s_port);
    }

  args = sshv2_gen_exec_args (request);

  child = gftp_exec (request, &fdm, &ptymfd, args);

  if (child == 0)
    exit (0);

  sshv2_free_args (args);

  if (child < 0)
    return (GFTP_ERETRYABLE);

  request->datafd = fdm;

  version = htonl (SSH_MY_VERSION);
  if ((ret = sshv2_send_command (request, SSH_FXP_INIT, (char *)
                                 &version, 4)) < 0)
    return (ret);

  ret = sshv2_start_login_sequence (request, fdm, ptymfd);
  if (ret < 0)
    return (ret);

  memset (&message, 0, sizeof (message));
  ret = sshv2_read_response (request, &message, -1);
  if (ret < 0)
    {
      sshv2_message_free (&message);
      return (ret);
    }
  else if (ret != SSH_FXP_VERSION)
    return (sshv2_wrong_response (request, &message));

  sshv2_message_free (&message);

  params->initialized = 1;
  request->logging_function (gftp_logging_misc, request,
                             _("Successfully logged into SSH server %s\n"),
                             request->hostname);

  if (sshv2_getcwd (request) < 0)
    {
      if (request->directory)
        g_free (request->directory);

      request->directory = g_strdup (".");
      if ((ret = sshv2_getcwd (request)) < 0)
        {
          gftp_disconnect (request);
          return (ret);
        }
    }

  return (0);
}
