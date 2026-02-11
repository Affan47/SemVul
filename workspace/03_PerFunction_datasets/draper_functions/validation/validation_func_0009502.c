take(const QDomElement &x) {
		if(!iqVerify(x, "", id()))
			return false;


		if (x.attribute("type") == "result") {
			QDomElement tag, q = queryTag(x);

			for (QDomNode n = q.firstChild(); !n.isNull(); n = n.nextSibling()) {
				QDomElement e = n.toElement();
				if (e.tagName() == "active")
					active_ = e.attribute("name");
				else if (e.tagName() == "default")
					default_ = e.attribute("name");
				else if (e.tagName() == "list")
					lists_.append(e.attribute("name"));
				else
					qWarning("privacy.cpp: Unknown tag in privacy lists.");

			}
			setSuccess();
		}
		else {
			setError(x);
		}
		return true;
	}
