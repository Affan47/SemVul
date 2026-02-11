certTypeCA() const {
#ifdef KSSL_HAVE_SSL

	return (flags & (65471L << 16)) ? true : certTypeSSLCA();
#endif
	return false;
}
