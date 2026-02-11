__getgroups (int n, gid_t *groups)
{
  return INLINE_SYSCALL (getgroups32, 2, n, groups);
}
