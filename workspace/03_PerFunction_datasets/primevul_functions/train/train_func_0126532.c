smtp_read_command(BOOL check_sync, unsigned buffer_lim)
{
int c;
int ptr = 0;
smtp_cmd_list *p;
BOOL hadnull = FALSE;

had_command_timeout = 0;
os_non_restarting_signal(SIGALRM, command_timeout_handler);

while ((c = (receive_getc)(buffer_lim)) != '\n' && c != EOF)
  {
  if (ptr >= SMTP_CMD_BUFFER_SIZE)
    {
    os_non_restarting_signal(SIGALRM, sigalrm_handler);
    return OTHER_CMD;
    }
  if (c == 0)
    {
    hadnull = TRUE;
    c = '?';
    }
  smtp_cmd_buffer[ptr++] = c;
  }

receive_linecount++;
os_non_restarting_signal(SIGALRM, sigalrm_handler);


if (c == EOF) return EOF_CMD;


while (ptr > 0 && isspace(smtp_cmd_buffer[ptr-1])) ptr--;
smtp_cmd_buffer[ptr] = 0;

DEBUG(D_receive) debug_printf("SMTP<< %s\n", smtp_cmd_buffer);


if (hadnull) return BADCHAR_CMD;


for (p = cmd_list; p < cmd_list_end; p++)
  {
#ifdef SUPPORT_PROXY

  if (proxy_session && f.proxy_session_failed && p->cmd != QUIT_CMD)
    continue;
#endif
  if (  p->len
     && strncmpic(smtp_cmd_buffer, US p->name, p->len) == 0
     && (  smtp_cmd_buffer[p->len-1] == ':'
        || smtp_cmd_buffer[p->len] == 0
	|| smtp_cmd_buffer[p->len] == ' '
     )  )
    {
    if (smtp_inptr < smtp_inend &&
        p->cmd < sync_cmd_limit &&
        check_sync &&
        smtp_enforce_sync &&
        sender_host_address != NULL &&
        !f.sender_host_notsocket)
      return BADSYN_CMD;


    smtp_cmd_argument = smtp_cmd_buffer + p->len;
    while (isspace(*smtp_cmd_argument)) smtp_cmd_argument++;
    Ustrcpy(smtp_data_buffer, smtp_cmd_argument);
    smtp_cmd_data = smtp_data_buffer;


    if (!p->is_mail_cmd)
      {
      if (count_nonmail == TRUE_UNSET) count_nonmail =
        verify_check_host(&smtp_accept_max_nonmail_hosts) != FAIL;
      if (count_nonmail && ++nonmail_command_count > smtp_accept_max_nonmail)
        return TOO_MANY_NONMAIL_CMD;
      }


    return (p->has_arg || *smtp_cmd_data == 0)? p->cmd : BADARG_CMD;
    }
  }

#ifdef SUPPORT_PROXY

if (proxy_session && f.proxy_session_failed)
  return PROXY_FAIL_IGNORE_CMD;
#endif


if (  smtp_inptr < smtp_inend
   && check_sync
   && smtp_enforce_sync
   && sender_host_address
   && !f.sender_host_notsocket)
  return BADSYN_CMD;

return OTHER_CMD;
}
