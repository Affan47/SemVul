setFlow(termios& term, FlowControl iflow, FlowControl oflow)
{
    switch (iflow) {
    case ClassModem::FLOW_NONE:
	term.c_iflag &= ~IXON;
	term.c_cflag &= ~CRTSCTS;
	break;
    case ClassModem::FLOW_XONXOFF:
	term.c_iflag |= IXON;
	term.c_cflag &= ~CRTSCTS;
	break;
    case ClassModem::FLOW_RTSCTS:
	term.c_iflag &= ~IXON;
	term.c_cflag |= CRTSCTS;
	break;
    }
    switch (oflow) {
    case ClassModem::FLOW_NONE:
	term.c_iflag &= ~IXOFF;
	term.c_cflag &= ~CRTSCTS;
	break;
    case ClassModem::FLOW_XONXOFF:
	term.c_iflag |= IXOFF;
	term.c_cflag &= ~CRTSCTS;
	break;
    case ClassModem::FLOW_RTSCTS:
	term.c_iflag &= ~IXOFF;
	term.c_cflag |= CRTSCTS;
	break;
    }
}
