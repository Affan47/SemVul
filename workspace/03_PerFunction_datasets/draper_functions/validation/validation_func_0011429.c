sigchldHandler()
{
   static int bcr_cnt = 0;
   int sock, pid, i;
   sng_int16 cidport ;
   dac_exitprocess_it out ;
   int status;


   u_short op ;

   while((pid=waitpid(-1,&status,WNOHANG)) > 0)
   {
	printf("CID. subp(%d) terminated \n", pid);
	fflush(stdout);

   	if (WIFEXITED(status)) {
        	status = WEXITSTATUS(status);
        	if (status == NORMAL_EXIT)
                	status = EXITTED;
        	else
                	status = FAILED;
   	} else status = KILLED;


    	op = htons(DAC_OP_EXIT_PROCESS)  ;
   	for (i = 0 ; i < TABLE_SIZE ; i++)
        {
           if ((table[i].used == USED) && (table[i].pid == pid))
           {
		printf("Setup exit status for (%d)\n", pid);
               if (status != EXITTED && table[i].fdd_start == FDD_ALIVE)
	       {
		  printf("Setup abnormal exit: term_stat == 0\n");
                  table[i].term_stat = 0;
	       }
               if (table[i].port)
                  if ((sock = get_socket()) != -1)
                   {
                      if (do_connect(sock, table[i].host, table[i].port))
                       {
                          writen(sock, (char *)&op, sizeof(u_short)) ;
                          out.retstatus = htons(status);
                          strcpy(out.name, table[i].name) ;
                          writen(sock, (char *)&out, sizeof(dac_exitprocess_it)) ;
                       }
                      close(sock) ;
                   }

               break ;
           }
    	}
#if HPUX | AIX | Linux | SunOs
	signal(SIGCHLD, sigchldHandler);
#endif
   }
   return;
}
