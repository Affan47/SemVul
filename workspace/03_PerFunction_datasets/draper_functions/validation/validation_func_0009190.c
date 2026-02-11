xonxoff_proc(int state)
{
    if(_inraw){
	if(state){
#if	HAS_TERMIOS

	    if(!(_raw_tty.c_iflag & IXON)){
		_raw_tty.c_iflag |= IXON;
		tcsetattr (STDIN_FD, TCSADRAIN, &_raw_tty);
	    }

#elif	HAS_TERMIO

	    if(!(_raw_tty.c_iflag & IXON)){
		_raw_tty.c_iflag |= IXON;
		(void)ioctl(STDIN_FD, TCSETAW, &_raw_tty);

#else

	    if(_raw_tchars.t_startc == -1 || _raw_tchars.t_stopc == -1){
		_raw_tchars.t_startc = 'Q' - '@';
		_raw_tchars.t_stopc  = 'S' - '@';
		(void)ioctl(STDIN_FD, TIOCSETC, &_raw_tchars);
	    }

#endif
	}
	else{
#if	HAS_TERMIOS

	    if(_raw_tty.c_iflag & IXON){
		_raw_tty.c_iflag &= ~IXON;
		tcsetattr (STDIN_FD, TCSADRAIN, &_raw_tty);
	    }

#elif	HAS_TERMIO

	    if(_raw_tty.c_iflag & IXON){
		_raw_tty.c_iflag &= ~IXON;
		(void)ioctl(STDIN_FD, TCSETAW, &_raw_tty);
	    }

#else
	    if(!(_raw_tchars.t_startc == -1 && _raw_tchars.t_stopc == -1)){
		_raw_tchars.t_startc = -1;
		_raw_tchars.t_stopc  = -1;
		(void)ioctl(STDIN_FD, TIOCSETC, &_raw_tchars);
	    }
#endif
	}
    }
}
