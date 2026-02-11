configure(Vector<String> &conf, ErrorHandler *errh)
{
    if (Args(conf, this, errh)
	.read_mp("MYADDR", _preferred_addr)
	.read_p("OTHERADDRS", _my_addrs)
	.complete() < 0)
	return -1;
    _my_addrs.push_back(_preferred_addr);
    return 0;
}
