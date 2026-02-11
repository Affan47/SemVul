gfm_getdirentsplusxattr_result(struct gfm_connection *gfm_server, void *closure)
{
	GFS_DirPlusXAttr dir = closure;
	gfarm_error_t e = gfm_client_getdirentsplusxattr_result(gfm_server,
	    &dir->n, dir->buffer, dir->stbuf, dir->nattrbuf,
	    dir->attrnamebuf, dir->attrvaluebuf, dir->attrsizebuf);

	if (e != GFARM_ERR_NO_ERROR)
		gflog_warning(GFARM_MSG_1002463, "getdirentsplusxattr result: %s",
		    gfarm_error_string(e));
	return (e);
}
