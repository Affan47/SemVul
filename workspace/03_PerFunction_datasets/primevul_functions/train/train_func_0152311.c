_dbus_read_socket_with_unix_fds (DBusSocket        fd,
                                 DBusString       *buffer,
                                 int               count,
                                 int              *fds,
                                 unsigned int     *n_fds) {
#ifndef HAVE_UNIX_FD_PASSING
  int r;

  if ((r = _dbus_read_socket(fd, buffer, count)) < 0)
    return r;

  *n_fds = 0;
  return r;

#else
  int bytes_read;
  int start;
  struct msghdr m;
  struct iovec iov;

  _dbus_assert (count >= 0);
  _dbus_assert (*n_fds <= DBUS_MAXIMUM_MESSAGE_UNIX_FDS);

  start = _dbus_string_get_length (buffer);

  if (!_dbus_string_lengthen (buffer, count))
    {
      errno = ENOMEM;
      return -1;
    }

  _DBUS_ZERO(iov);
  iov.iov_base = _dbus_string_get_data_len (buffer, start, count);
  iov.iov_len = count;

  _DBUS_ZERO(m);
  m.msg_iov = &iov;
  m.msg_iovlen = 1;


  m.msg_controllen = CMSG_SPACE(*n_fds * sizeof(int));


  m.msg_control = alloca(m.msg_controllen);
  memset(m.msg_control, 0, m.msg_controllen);


  m.msg_controllen = CMSG_LEN (*n_fds * sizeof(int));

 again:

  bytes_read = recvmsg (fd.fd, &m, 0
#ifdef MSG_CMSG_CLOEXEC
                       |MSG_CMSG_CLOEXEC
#endif
                       );

  if (bytes_read < 0)
    {
      if (errno == EINTR)
        goto again;
      else
        {

          _dbus_string_set_length (buffer, start);
          return -1;
        }
    }
  else
    {
      struct cmsghdr *cm;
      dbus_bool_t found = FALSE;

      for (cm = CMSG_FIRSTHDR(&m); cm; cm = CMSG_NXTHDR(&m, cm))
        if (cm->cmsg_level == SOL_SOCKET && cm->cmsg_type == SCM_RIGHTS)
          {
            size_t i;
            int *payload = (int *) CMSG_DATA (cm);
            size_t payload_len_bytes = (cm->cmsg_len - CMSG_LEN (0));
            size_t payload_len_fds = payload_len_bytes / sizeof (int);
            size_t fds_to_use;


            _DBUS_STATIC_ASSERT (sizeof (size_t) >= sizeof (unsigned int));

            if (_DBUS_LIKELY (payload_len_fds <= (size_t) *n_fds))
              {

                fds_to_use = payload_len_fds;
              }
            else
              {


                fds_to_use = (size_t) *n_fds;


                for (i = fds_to_use; i < payload_len_fds; i++)
                  {
                    close (payload[i]);
                  }
              }

            memcpy (fds, payload, fds_to_use * sizeof (int));
            found = TRUE;


            *n_fds = (unsigned int) fds_to_use;


            for (i = 0; i < fds_to_use; i++)
              _dbus_fd_set_close_on_exec(fds[i]);

            break;
          }

      if (!found)
        *n_fds = 0;

      if (m.msg_flags & MSG_CTRUNC)
        {
          unsigned int i;


          for (i = 0; i < *n_fds; i++)
            close (fds[i]);

          *n_fds = 0;
          errno = ENOSPC;
          _dbus_string_set_length (buffer, start);
          return -1;
        }


      _dbus_string_set_length (buffer, start + bytes_read);

#if 0
      if (bytes_read > 0)
        _dbus_verbose_bytes_of_string (buffer, start, bytes_read);
#endif

      return bytes_read;
    }
#endif
}
