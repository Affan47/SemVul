zxlog_path(zxid_conf* cf,
			  struct zx_str* entid,
			  struct zx_str* objid,
			  const char* dir,
			  const char* kind,
			  int create_dirs)
{
  struct stat st;
  int dir_len = strlen(dir);
  int kind_len = strlen(kind);
  int len = cf->path_len + sizeof("log/")-1 + dir_len + 27 + kind_len + 27;
  char* s = ZX_ALLOC(cf->ctx, len+1);
  char* p;

  if (!entid) {
    ERR("No EntityID supplied %p dir(%s) kind(%s)", objid, STRNULLCHK(dir), STRNULLCHK(kind));
    ZX_FREE(cf->ctx, s);
    return 0;
  }

  memcpy(s, cf->path, cf->path_len);
  p = s + cf->path_len;
  memcpy(p, "log/", sizeof("log/"));
  p += sizeof("log/")-1;
  if (stat(s, &st)) {
    ERR("zxid log directory missing path(%s): giving up (stat: %d %s; euid=%d egid=%d). Consider checking permissions and running zxmkdirs.sh", s, errno, STRERROR(errno), geteuid(), getegid());
    goto nodir;
  }

  memcpy(p, dir, dir_len+1);
  p += dir_len;
  if (!zx_create_dir_with_check(cf, s, create_dirs)) goto nodir;

  sha1_safe_base64(p, entid->len, entid->s);
  p[27] = 0;
  p+=27;
  if (!zx_create_dir_with_check(cf, s, create_dirs)) goto nodir;

  memcpy(p, kind, kind_len+1);
  p += kind_len;
  if (!zx_create_dir_with_check(cf, s, create_dirs)) goto nodir;

  sha1_safe_base64(p, objid->len, objid->s);
  p[27] = 0;
  p+=27;
  return zx_ref_len_str(cf->ctx, len, s);
 nodir:
  ZX_FREE(cf->ctx, s);
  return 0;
}
