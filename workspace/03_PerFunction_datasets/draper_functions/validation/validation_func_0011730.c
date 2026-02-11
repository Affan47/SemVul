is_dir_p (const char *dir, size_t dirlen, const char *fname,
	  glob_t *pglob, int flags)
{
  size_t fnamelen = strlen (fname);
  char *fullname = __alloca (dirlen + 1 + fnamelen + 1);
  struct stat st;
  struct_stat64 st64;

  mempcpy (mempcpy (mempcpy (fullname, dir, dirlen), "/", 1),
	   fname, fnamelen + 1);

  return ((flags & GLOB_ALTDIRFUNC)
	  ? (*pglob->gl_stat) (fullname, &st) == 0 && S_ISDIR (st.st_mode)
	  : __stat64 (fullname, &st64) == 0 && S_ISDIR (st64.st_mode));
}
