transport_check_waiting(const uschar *transport_name, const uschar *hostname,
  int local_message_max, uschar *new_message_id, BOOL *more, oicf oicf_func, void *oicf_data)
{
dbdata_wait *host_record;
int host_length;
open_db dbblock;
open_db *dbm_file;

int         i;
struct stat statbuf;

*more = FALSE;

DEBUG(D_transport)
  {
  debug_printf("transport_check_waiting entered\n");
  debug_printf("  sequence=%d local_max=%d global_max=%d\n",
    continue_sequence, local_message_max, connection_max_messages);
  }


if (connection_max_messages >= 0) local_message_max = connection_max_messages;
if (local_message_max > 0 && continue_sequence >= local_message_max)
  {
  DEBUG(D_transport)
    debug_printf("max messages for one connection reached: returning\n");
  return FALSE;
  }


if (!(dbm_file = dbfn_open(string_sprintf("wait-%.200s", transport_name),
			  O_RDWR, &dbblock, TRUE)))
  return FALSE;


if (!(host_record = dbfn_read(dbm_file, hostname)))
  {
  dbfn_close(dbm_file);
  DEBUG(D_transport) debug_printf("no messages waiting for %s\n", hostname);
  return FALSE;
  }


if (host_record->count > WAIT_NAME_MAX)
  {
  dbfn_close(dbm_file);
  log_write(0, LOG_MAIN|LOG_PANIC, "smtp-wait database entry for %s has bad "
    "count=%d (max=%d)", hostname, host_record->count, WAIT_NAME_MAX);
  return FALSE;
  }


host_length = host_record->count * MESSAGE_ID_LENGTH;

while (1)
  {
  msgq_t      *msgq;
  int         msgq_count = 0;
  int         msgq_actual = 0;
  BOOL        bFound = FALSE;
  BOOL        bContinuation = FALSE;


  msgq = store_malloc(sizeof(msgq_t) * host_record->count);
  msgq_count = host_record->count;
  msgq_actual = msgq_count;

  for (i = 0; i < host_record->count; ++i)
    {
    msgq[i].bKeep = TRUE;

    Ustrncpy(msgq[i].message_id, host_record->text + (i * MESSAGE_ID_LENGTH),
      MESSAGE_ID_LENGTH);
    msgq[i].message_id[MESSAGE_ID_LENGTH] = 0;
    }


  for (i = 0; i < msgq_count; ++i)
    if (Ustrcmp(msgq[i].message_id, message_id) == 0)
      {
      msgq[i].bKeep = FALSE;
      break;
      }


  for (i = msgq_count - 1; i >= 0; --i) if (msgq[i].bKeep)
    {
    uschar subdir[2];

    subdir[0] = split_spool_directory ? msgq[i].message_id[5] : 0;
    subdir[1] = 0;

    if (Ustat(spool_fname(US"input", subdir, msgq[i].message_id, US"-D"),
	      &statbuf) != 0)
      msgq[i].bKeep = FALSE;
    else if (!oicf_func || oicf_func(msgq[i].message_id, oicf_data))
      {
      Ustrcpy(new_message_id, msgq[i].message_id);
      msgq[i].bKeep = FALSE;
      bFound = TRUE;
      break;
      }
    }


  for (msgq_actual = 0, i = 0; i < msgq_count; ++i)
    if (msgq[i].bKeep)
      msgq_actual++;


  if (msgq_actual <= 0)
    {
    host_length = 0;
    host_record->count = 0;
    }
  else
    {
    host_length = msgq_actual * MESSAGE_ID_LENGTH;
    host_record->count = msgq_actual;

    if (msgq_actual < msgq_count)
      {
      int new_count;
      for (new_count = 0, i = 0; i < msgq_count; ++i)
	if (msgq[i].bKeep)
	  Ustrncpy(&host_record->text[new_count++ * MESSAGE_ID_LENGTH],
	    msgq[i].message_id, MESSAGE_ID_LENGTH);

      host_record->text[new_count * MESSAGE_ID_LENGTH] = 0;
      }
    }


  while (host_length <= 0)
    {
    int i;
    dbdata_wait * newr = NULL;
    uschar buffer[256];


    for (i = host_record->sequence - 1; i >= 0 && !newr; i--)
      {
      sprintf(CS buffer, "%.200s:%d", hostname, i);
      newr = dbfn_read(dbm_file, buffer);
      }


    if (!newr)
      {
      dbfn_delete(dbm_file, hostname);
      break;
      }


    dbfn_delete(dbm_file, buffer);
    host_record = newr;
    host_length = host_record->count * MESSAGE_ID_LENGTH;

    bContinuation = TRUE;
    }

  if (bFound)
    {
    store_free (msgq);
    break;
    }


  if (host_length <= 0)
    {
    dbfn_close(dbm_file);
    DEBUG(D_transport) debug_printf("waiting messages already delivered\n");
    return FALSE;
    }


  if (!bContinuation)
    {
    Ustrcpy(new_message_id, message_id);
    dbfn_close(dbm_file);
    return FALSE;
    }

  store_free(msgq);
  }


if (host_length > 0)
  {
  host_record->count = host_length/MESSAGE_ID_LENGTH;

  dbfn_write(dbm_file, hostname, host_record, (int)sizeof(dbdata_wait) + host_length);
  *more = TRUE;
  }

dbfn_close(dbm_file);
return TRUE;
}
