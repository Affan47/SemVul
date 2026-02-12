char* imap_set_flags (IMAP_DATA* idata, HEADER* h, char* s, int *server_changes)
{
  CONTEXT* ctx = idata->ctx;
  IMAP_HEADER newh;
  IMAP_HEADER_DATA old_hd;
  IMAP_HEADER_DATA* hd;
  unsigned char readonly;
  int local_changes;

  local_changes = h->changed;

  memset (&newh, 0, sizeof (newh));
  hd = h->data;
  newh.data = hd;

  memcpy (&old_hd, hd, sizeof(old_hd));

  dprint (2, (debugfile, "imap_set_flags: parsing FLAGS\n"));
  if ((s = msg_parse_flags (&newh, s)) == NULL)
    return NULL;


  readonly = ctx->readonly;
  ctx->readonly = 0;


  imap_set_changed_flag (ctx, h, local_changes, server_changes,
                         MUTT_OLD, old_hd.old, hd->old, h->old);
  imap_set_changed_flag (ctx, h, local_changes, server_changes,
                         MUTT_READ, old_hd.read, hd->read, h->read);
  imap_set_changed_flag (ctx, h, local_changes, server_changes,
                         MUTT_DELETE, old_hd.deleted, hd->deleted, h->deleted);
  imap_set_changed_flag (ctx, h, local_changes, server_changes,
                         MUTT_FLAG, old_hd.flagged, hd->flagged, h->flagged);
  imap_set_changed_flag (ctx, h, local_changes, server_changes,
                         MUTT_REPLIED, old_hd.replied, hd->replied, h->replied);


  if (!local_changes)
    h->changed = 0;
  ctx->changed &= ~readonly;
  ctx->readonly = readonly;

  return s;
}
