received_header_gen(void)
{
uschar *received;
uschar *timestamp;
header_line *received_header= header_list;

timestamp = expand_string(US"${tod_full}");
if (recipients_count == 1) received_for = recipients_list[0].address;
received = expand_string(received_header_text);
received_for = NULL;

if (!received)
  {
  if(spool_name[0] != 0)
    Uunlink(spool_name);
  log_write(0, LOG_MAIN|LOG_PANIC_DIE, "Expansion of \"%s\" "
    "(received_header_text) failed: %s", string_printing(received_header_text),
      expand_string_message);
  }


if (received[0] == 0)
  {
  received_header->text = string_sprintf("Received: ; %s\n", timestamp);
  received_header->type = htype_old;
  }
else
  {
  received_header->text = string_sprintf("%s; %s\n", received, timestamp);
  received_header->type = htype_received;
  }

received_header->slen = Ustrlen(received_header->text);

DEBUG(D_receive) debug_printf(">>Generated Received: header line\n%c %s",
  received_header->type, received_header->text);
}
