_PLfuse_release (const char *file, struct fuse_file_info *fi) {
	int rv;
	int flags = fi->flags;
#if FUSE_VERSION >= 29 && !defined(PERL_HAS_64BITINT)
	char *temp;
#endif
	FUSE_CONTEXT_PRE;
	DEBUGf("release begin\n");
	ENTER;
	SAVETMPS;
	PUSHMARK(SP);
	XPUSHs(file ? sv_2mortal(newSVpv(file,0)) : &PL_sv_undef);
	XPUSHs(sv_2mortal(newSViv(flags)));
	XPUSHs(FH_GETHANDLE(fi));
#if FUSE_VERSION >= 29
	XPUSHs(fi->flock_release ? sv_2mortal(newSViv(1)) : &PL_sv_undef);
# ifdef PERL_HAS_64BITINT
	XPUSHs(sv_2mortal(newSViv(fi->lock_owner)));
# else
	if (asprintf(&temp, "%llu", fi->lock_owner) == -1)
		croak("Memory allocation failure!");
	XPUSHs(sv_2mortal(newSVpv(temp, 0)));
# endif
#endif
	PUTBACK;
	rv = call_sv(MY_CXT.callback[19],G_SCALAR);
	SPAGAIN;
	rv = (rv ? POPi : 0);
	FH_RELEASEHANDLE(fi);
	FREETMPS;
	LEAVE;
	PUTBACK;
	DEBUGf("release end: %i\n",rv);
	FUSE_CONTEXT_POST;
	return rv;
}
