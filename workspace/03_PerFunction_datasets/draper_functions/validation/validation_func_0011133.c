createRSA(int bits, int exp, const QString &provider)
{
	if(isBusy())
		return PrivateKey();

	d->key = PrivateKey();
	d->wasBlocking = d->blocking;
	d->k = static_cast<RSAContext *>(getContext("rsa", provider));
	d->dest = static_cast<PKeyContext *>(getContext("pkey", d->k->provider()));

	if(!d->blocking)
	{
		d->k->moveToThread(thread());
		d->k->setParent(d);
		connect(d->k, SIGNAL(finished()), d, SLOT(done()));
		static_cast<RSAContext *>(d->k)->createPrivate(bits, exp, false);
	}
	else
	{
		static_cast<RSAContext *>(d->k)->createPrivate(bits, exp, true);
		d->done();
	}

	return d->key;
}
