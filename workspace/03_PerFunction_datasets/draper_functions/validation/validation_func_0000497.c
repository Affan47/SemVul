shell(ssh_session session){
    ssh_channel channel;
    struct termios terminal_local;
    int interactive=isatty(0);
    channel = ssh_channel_new(session);
    if(interactive){
        tcgetattr(0,&terminal_local);
        memcpy(&terminal,&terminal_local,sizeof(struct termios));
    }
    if(ssh_channel_open_session(channel)){
        printf("error opening channel : %s\n",ssh_get_error(session));
        return;
    }
    chan=channel;
    if(interactive){
        ssh_channel_request_pty(channel);
        sizechanged();
    }
    if(ssh_channel_request_shell(channel)){
        printf("Requesting shell : %s\n",ssh_get_error(session));
        return;
    }
    if(interactive){
        cfmakeraw(&terminal_local);
        tcsetattr(0,TCSANOW,&terminal_local);
        setsignal();
    }
    signal(SIGTERM,do_cleanup);
    select_loop(session,channel);
    if(interactive)
    	do_cleanup(0);
}
