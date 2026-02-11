ftp_lite_send_command( struct ftp_lite_server *s, const char *fmt, ... )
{
	char buffer[FTP_LITE_LINE_MAX];
	va_list args;

	va_start(args,fmt);
	vsprintf(buffer,fmt,args);
	va_end(args);

	if(!strncmp(buffer,"PASS",4)) {
		debug(D_FTP,"%s PASS ******\n",s->hostname);
	} else {
		debug(D_FTP,"%s %s\n",s->hostname,buffer);
	}

	switch(s->authtype) {
		case PLAIN:
			return ftp_lite_send_command_raw(s,buffer);
		case GLOBUS_GSS:
			return ftp_lite_send_command_gss(s,buffer);
		default:
			errno = ENOTSUP;
			return 0;
	}
}
