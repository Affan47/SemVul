encode(const QString &jid)
{
	QString jid2;

	for(int n = 0; n < jid.length(); ++n) {
		if(jid.at(n) == '@') {
			jid2.append("_at_");
		}
		else if(jid.at(n) == '.') {
			jid2.append('.');
		}
		else if(!jid.at(n).isLetterOrNumber()) {

			QString hex;
			hex.sprintf("%%%02X", jid.at(n).latin1());
			jid2.append(hex);
		}
		else {
			jid2.append(jid.at(n));
		}
	}

	return jid2;
}
