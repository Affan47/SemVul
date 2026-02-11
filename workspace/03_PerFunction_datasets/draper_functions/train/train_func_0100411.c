folder_info_get_msg_by_uid(struct folder_ref_info * ref_info,
    char * uid)
{
  chashdatum key;
  chashdatum data;
  mailmessage * msg;
  int r;

  key.data = uid;
  key.len = strlen(uid);
  r = chash_get(ref_info->uid_hash, &key, &data);
  if (r < 0)
    return NULL;

  msg = data.data;

  return msg;
}
