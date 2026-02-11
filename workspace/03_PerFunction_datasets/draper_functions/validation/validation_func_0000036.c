request(const Jid &to, const QString &sid, const StreamHostList &hosts, bool fast, bool udp)
{
	d->mode = 0;

	QDomElement iq;
	d->to = to;
	iq = createIQ(doc(), "set", to.full(), id());
	QDomElement query = doc()->createElement("query");
	query.setAttribute("xmlns", "http://jabber.org/protocol/bytestreams");
	query.setAttribute("sid", sid);
	query.setAttribute("mode", udp ? "udp" : "tcp" );
	iq.appendChild(query);
	for(StreamHostList::ConstIterator it = hosts.constBegin(); it != hosts.constEnd(); ++it) {
		QDomElement shost = doc()->createElement("streamhost");
		shost.setAttribute("jid", (*it).jid().full());
		shost.setAttribute("host", (*it).host());
		shost.setAttribute("port", QString::number((*it).port()));
		if((*it).isProxy()) {
			QDomElement p = doc()->createElement("proxy");
			p.setAttribute("xmlns", "http://affinix.com/jabber/stream");
			shost.appendChild(p);
		}
		query.appendChild(shost);
	}
	if(fast) {
		QDomElement e = doc()->createElement("fast");
		e.setAttribute("xmlns", "http://affinix.com/jabber/stream");
		query.appendChild(e);
	}
	d->iq = iq;
}
