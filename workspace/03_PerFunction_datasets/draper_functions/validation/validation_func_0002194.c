write_pid_file(uid_t usr, gid_t grp){
	int fd;
	int result=0;
	pid_t pid=0;
	char pbuf[16];


	if(pid_file==NULL)
		return OK;


	if((fd=open(pid_file,O_RDONLY))>=0){

		result=read(fd,pbuf,(sizeof pbuf)-1);

		close(fd);

		if(result>0){

			pbuf[result]='\x0';
			pid=(pid_t)atoi(pbuf);


			if(pid && (pid==getpid() || kill(pid,0)<0))
				unlink(pid_file);


			else{
				syslog(LOG_ERR,"There's already an NSCA server running (PID %lu).  Bailing out...",(unsigned long)pid);
				return ERROR;
			        }
		        }
	        }


	if((fd=open(pid_file,O_WRONLY | O_CREAT,0644))>=0){
		sprintf(pbuf,"%d\n",(int)getpid());
		write(fd,pbuf,strlen(pbuf));
		fchown(fd,usr,grp);
		close(fd);
		wrote_pid_file=TRUE;
	        }
	else{
		syslog(LOG_ERR,"Cannot write to pidfile '%s' - check your privileges.",pid_file);
	        }

	return OK;
        }
