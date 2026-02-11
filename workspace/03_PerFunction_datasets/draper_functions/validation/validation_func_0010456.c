maildir_new(const char * path)
{
  struct maildir * md;

  md = malloc(sizeof(* md));
  if (md == NULL)
    goto err;

  md->mdir_counter = 0;
  md->mdir_mtime_new = (time_t) -1;
  md->mdir_mtime_cur = (time_t) -1;

  md->mdir_pid = getpid();
  gethostname(md->mdir_hostname, sizeof(md->mdir_hostname));
  strncpy(md->mdir_path, path, sizeof(md->mdir_path));
  md->mdir_path[PATH_MAX - 1] = '\0';

  md->mdir_msg_list = carray_new(128);
  if (md->mdir_msg_list == NULL)
    goto free;

  md->mdir_msg_hash = chash_new(CHASH_DEFAULTSIZE, CHASH_COPYNONE);
  if (md->mdir_msg_hash == NULL)
    goto free_msg_list;

  return md;

 free_msg_list:
  carray_free(md->mdir_msg_list);
 free:
  free(md);
 err:
  return NULL;
}
