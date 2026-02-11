layer_readyRead(const QByteArray &a)
{
	SecureLayer *s = (SecureLayer *)sender();
	QList<SecureLayer*>::Iterator it(d->layers.begin());
	while((*it) != s) {
		Q_ASSERT(it != d->layers.end());
		++it;
	}
	Q_ASSERT(it != d->layers.end());


	++it;
	if (it != d->layers.end()) {
		s = (*it);
		s->writeIncoming(a);
	}
	else {
		incomingData(a);
	}
}
