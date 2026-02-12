static int make_msg_set(struct Mailbox *m, struct Buffer *buf, int flag,
                        bool changed, bool invert, int *pos)
{
  int count = 0;
  unsigned int setstart = 0;
  int n;
  bool started = false;

  struct ImapAccountData *adata = imap_adata_get(m);
  if (!adata || (adata->mailbox != m))
    return -1;

  for (n = *pos; (n < m->msg_count) && (mutt_buffer_len(buf) < IMAP_MAX_CMDLEN); n++)
  {
    struct Email *e = m->emails[n];
    if (!e)
      break;
    bool match = false;


    if (e->active && (e->index != INT_MAX))
    {
      switch (flag)
      {
        case MUTT_DELETED:
          if (e->deleted != imap_edata_get(e)->deleted)
            match = invert ^ e->deleted;
          break;
        case MUTT_FLAG:
          if (e->flagged != imap_edata_get(e)->flagged)
            match = invert ^ e->flagged;
          break;
        case MUTT_OLD:
          if (e->old != imap_edata_get(e)->old)
            match = invert ^ e->old;
          break;
        case MUTT_READ:
          if (e->read != imap_edata_get(e)->read)
            match = invert ^ e->read;
          break;
        case MUTT_REPLIED:
          if (e->replied != imap_edata_get(e)->replied)
            match = invert ^ e->replied;
          break;
        case MUTT_TAG:
          if (e->tagged)
            match = true;
          break;
        case MUTT_TRASH:
          if (e->deleted && !e->purge)
            match = true;
          break;
      }
    }

    if (match && (!changed || e->changed))
    {
      count++;
      if (setstart == 0)
      {
        setstart = imap_edata_get(e)->uid;
        if (started)
        {
          mutt_buffer_add_printf(buf, ",%u", imap_edata_get(e)->uid);
        }
        else
        {
          mutt_buffer_add_printf(buf, "%u", imap_edata_get(e)->uid);
          started = true;
        }
      }

      else if (n == (m->msg_count - 1))
        mutt_buffer_add_printf(buf, ":%u", imap_edata_get(e)->uid);
    }


    else if (setstart && (e->active || (n == adata->mailbox->msg_count - 1)))
    {
      if (imap_edata_get(m->emails[n - 1])->uid > setstart)
        mutt_buffer_add_printf(buf, ":%u", imap_edata_get(m->emails[n - 1])->uid);
      setstart = 0;
    }
  }

  *pos = n;

  return count;
}
