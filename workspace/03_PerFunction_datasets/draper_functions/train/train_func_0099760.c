sftp_normalize_ownergroup(struct allocator *a, struct sftpattr *attrs) {
  uint32_t rc = SSH_FX_OK;

  switch(attrs->valid & (SSH_FILEXFER_ATTR_UIDGID
                         |SSH_FILEXFER_ATTR_OWNERGROUP)) {
  case SSH_FILEXFER_ATTR_UIDGID:
    if((attrs->owner = sftp_uid2name(a, attrs->uid))
       && (attrs->group = sftp_gid2name(a, attrs->gid)))
      attrs->valid |= SSH_FILEXFER_ATTR_OWNERGROUP;
    break;
  case SSH_FILEXFER_ATTR_OWNERGROUP:
    if((attrs->uid = sftp_name2uid(attrs->owner)) == (uid_t)-1)
      rc = SSH_FX_OWNER_INVALID;
    if((attrs->gid = sftp_name2gid(attrs->group)) == (gid_t)-1)
      rc = SSH_FX_GROUP_INVALID;
    if(rc == SSH_FX_OK)
      attrs->valid |= SSH_FILEXFER_ATTR_UIDGID;
    break;
  }
  return rc;
}
