deliver_get_sender_address (uschar * id)
{
int rc;
uschar * new_sender_address,
       * save_sender_address;
BOOL save_qr = queue_running;
uschar * spoolname;


queue_running = TRUE;


deliver_datafile = spool_open_datafile(id);
queue_running = save_qr;
if (deliver_datafile < 0)
  return NULL;


spoolname = string_sprintf("%s-H", id);
save_sender_address = sender_address;

rc = spool_read_header(spoolname, TRUE, TRUE);

new_sender_address = sender_address;
sender_address = save_sender_address;

if (rc != spool_read_OK)
  return NULL;

assert(new_sender_address);

(void)close(deliver_datafile);
deliver_datafile = -1;

return new_sender_address;
}
