set_attributes (int fd, int baud_rate, MonoParity parity, int dataBits, MonoStopBits stopBits, MonoHandshake handshake)
{
	struct termios newtio;

	if (tcgetattr (fd, &newtio) == -1)
		return FALSE;

	newtio.c_cflag |=  (CLOCAL | CREAD);
	newtio.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ISIG | IEXTEN );
	newtio.c_oflag &= ~(OPOST);
	newtio.c_iflag = IGNBRK;


	baud_rate = setup_baud_rate (baud_rate);


	newtio.c_cflag &= ~CSIZE;
	switch (dataBits)
	{
	case 5:
	    newtio.c_cflag |= CS5;
	    break;
	case 6:
	    newtio.c_cflag |= CS6;
	    break;
	case 7:
	    newtio.c_cflag |= CS7;
	    break;
	case 8:
	default:
		newtio.c_cflag |= CS8;
		break;
	}


	switch (stopBits)
	{
	case NoneStopBits:

		break;
	case One:

	    newtio.c_cflag &= ~CSTOPB;
		break;
	case Two:
		newtio.c_cflag |= CSTOPB;
		break;
	case OnePointFive:

		break;
	}


	newtio.c_iflag &= ~(INPCK | ISTRIP );

	switch (parity)
	{
	case NoneParity:
	    newtio.c_cflag &= ~(PARENB | PARODD);
	    break;

	case Odd:
	    newtio.c_cflag |= PARENB | PARODD;
	    break;

	case Even:
	    newtio.c_cflag &= ~(PARODD);
	    newtio.c_cflag |= (PARENB);
	    break;

	case Mark:

	    break;
	case Space:

	    break;
	}

   	newtio.c_iflag &= ~(IXOFF | IXON);
#ifdef CRTSCTS
	newtio.c_cflag &= ~CRTSCTS;
#endif

	switch (handshake)
	{
	case NoneHandshake:

		break;
	case RequestToSend:
#ifdef CRTSCTS
		newtio.c_cflag |= CRTSCTS;
#endif
		break;
	case RequestToSendXOnXOff:
#ifdef CRTSCTS
		newtio.c_cflag |= CRTSCTS;
#endif

	case XOnXOff:
	    newtio.c_iflag |= IXOFF | IXON;
		break;
	}

	if (cfsetospeed (&newtio, baud_rate) < 0 || cfsetispeed (&newtio, baud_rate) < 0 ||
	    tcsetattr (fd, TCSANOW, &newtio) < 0)
	{
		return FALSE;
	}
	else
	{
	return TRUE;
	}
}
