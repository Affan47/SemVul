rploadgov(int4 srcnode, int4 destnode, CONST char *filename, int4 rtflags,
    char **argv, struct penv *env, int4 *pid, int4 *idx)
{
    int			r;
    int4		argvtag;
    int4		progtag;
    int4		envsize;
    char		*fullpath;
    char		*cwd;


    if ((destnode == LOCAL || destnode == getnodeid())
	    && LAM_isNullStr(env->pe_wrkdir) && !(rtflags & RTF_APPWD)) {
	if ((cwd = getworkdir()) == 0)
  	    return(LAMERROR);
	lam_strncpy(env->pe_wrkdir, cwd, LAM_PATH_MAX);
	free(cwd);
    }


    if (srcnode == destnode) {

	if ((srcnode == LOCAL) || (srcnode == getnodeid())) {
	    fullpath = sfh_path_env_findv((char*) filename, X_OK,
				env->pe_envv, env->pe_wrkdir);
	    if (fullpath == 0)
		return(LAMERROR);

	    r = rpcreatev(srcnode, fullpath, rtflags, argv, env, pid, idx);
	    free(fullpath);
	}
	else {
	    r = rpcreatev(srcnode, filename, rtflags, argv, env, pid, idx);
	}

	return(r);
    }


    argvtag = 0;
    if (rflatv(destnode, argv, env, &envsize, &argvtag)) {
	return(LAMERROR);
    }


    progtag = lam_getpid();
    if (rload(srcnode, destnode, progtag, filename)) {
	if (argvtag)
	    rflclean(destnode, argvtag);
	return(LAMERROR);
    }


    return(rpgov(destnode, progtag, rtflags,
		argvtag, envsize, env->pe_wrkdir, env->pe_rank, pid, idx));
}
