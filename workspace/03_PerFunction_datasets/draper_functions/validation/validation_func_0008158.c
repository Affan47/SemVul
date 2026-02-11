operator>> (unsigned short& n_)
{
	u_short val;
	if (read ((char*) &val, sizeof(u_short)) == sizeof(u_short)) {
		n_ = (u_short) ntohs ((u_short)val);
	}
	else {
		setstate (Socket::eofbit|Socket::failbit);
	}
	return *this;
}
