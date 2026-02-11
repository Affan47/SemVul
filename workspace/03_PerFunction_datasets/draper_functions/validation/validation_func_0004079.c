sendData(const Jid &to, const IBBData &ibbData)
{
	d->mode = ModeSendData;
	QDomElement iq;
	d->to = to;
	d->bytesWritten = ibbData.data.size();
	iq = createIQ(doc(), "set", to.full(), id());
	iq.appendChild(ibbData.toXml(doc()));
	d->iq = iq;
}
