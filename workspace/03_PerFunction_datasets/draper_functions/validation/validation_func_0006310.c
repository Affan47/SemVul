bsock_getpeereid(VALUE self)
{
#if defined(HAVE_GETPEEREID)
    rb_io_t *fptr;
    uid_t euid;
    gid_t egid;
    GetOpenFile(self, fptr);
    if (getpeereid(fptr->fd, &euid, &egid) == -1)
	rb_sys_fail("getpeereid");
    return rb_assoc_new(UIDT2NUM(euid), GIDT2NUM(egid));
#elif defined(SO_PEERCRED)
    rb_io_t *fptr;
    struct ucred cred;
    socklen_t len = sizeof(cred);
    GetOpenFile(self, fptr);
    if (getsockopt(fptr->fd, SOL_SOCKET, SO_PEERCRED, &cred, &len) == -1)
	rb_sys_fail("getsockopt(SO_PEERCRED)");
    return rb_assoc_new(UIDT2NUM(cred.uid), GIDT2NUM(cred.gid));
#elif defined(HAVE_GETPEERUCRED)
    rb_io_t *fptr;
    ucred_t *uc = NULL;
    VALUE ret;
    GetOpenFile(self, fptr);
    if (getpeerucred(fptr->fd, &uc) == -1)
	rb_sys_fail("getpeerucred");
    ret = rb_assoc_new(UIDT2NUM(ucred_geteuid(uc)), GIDT2NUM(ucred_getegid(uc)));
    ucred_free(uc);
    return ret;
#endif
}
