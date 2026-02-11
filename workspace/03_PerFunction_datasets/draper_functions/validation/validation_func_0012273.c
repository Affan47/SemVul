configure(Vector<String> &conf, ErrorHandler *errh)
{
    _notifier.initialize(Notifier::EMPTY_NOTIFIER, router());
    if (Args(conf, this, errh).read_p("QUANTUM", _quantum).complete() < 0)
	return -1;
    if (_quantum <= 0)
	return errh->error("bad QUANTUM");
    return 0;
}
