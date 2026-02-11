configure(Vector<String> &conf, ErrorHandler *errh)
{
    if (Args(conf, this, errh)
	.read_mp("LATENCY", _latency)
	.read_mp("BANDWIDTH", BandwidthArg(), _bandwidth).complete() < 0)
	return -1;
    if (_bandwidth < 100)
	return errh->error("bandwidth too small, minimum 100Bps");
    _bandwidth /= 100;
    return 0;
}
