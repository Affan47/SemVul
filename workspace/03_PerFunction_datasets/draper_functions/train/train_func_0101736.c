configure(Vector<String> &conf, ErrorHandler *errh)
{
    if (cp_va_kparse(conf, this, errh,
		     "SRC", cpkP+cpkM, cpIPAddress, &_src,
		     "DST", cpkP+cpkM, cpIPAddress, &_dst,
		     "IDENTIFIER", 0, cpUnsignedShort, &_icmp_id,
		     cpEnd) < 0)
	return -1;

#if HAVE_FAST_CHECKSUM && FAST_CHECKSUM_ALIGNED
    {
	int ans, c, o;
	ans = AlignmentInfo::query(this, 0, c, o);
	_aligned = (ans && c == 4 && o == 0);
	if (!_aligned)
	    errh->warning("IP header unaligned, cannot use fast IP checksum");
	if (!ans)
	    errh->message("(Try passing the configuration through `click-align'.)");
    }
#endif

    return 0;
}
