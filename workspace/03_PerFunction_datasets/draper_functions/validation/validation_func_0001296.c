doStep(const QDomElement &e)
{

	if(delayedError) {
		if(isIncoming())
			return errorAndClose(errCond, errText, errAppSpec);
		else
			return error(errorCode);
	}


	if(doShutdown) {
		doShutdown = false;
		return close();
	}

	if(!e.isNull()) {

		if(e.namespaceURI() == NS_ETHERX && e.tagName() == "error") {
			extractStreamError(e);
			return error(ErrStream);
		}
	}

	if(ready) {

		if(stanzasWritten > 0) {
			--stanzasWritten;
			event = EStanzaSent;
			return true;
		}

		if(!sendList.isEmpty()) {
			SendItem i;
			{
				QList<SendItem>::Iterator it = sendList.begin();
				i = (*it);
				sendList.erase(it);
			}


			if(!i.stanzaToSend.isNull()) {
				++stanzasPending;
				writeElement(i.stanzaToSend, TypeStanza, true);
				event = ESend;
			}

			else if(!i.stringToSend.isEmpty()) {
				writeString(i.stringToSend, TypeDirect, true);
				event = ESend;
			}

			else if(i.doWhitespace) {
				writeString("\n", TypePing, false);
				event = ESend;
			}
			return true;
		}
		else {

			if(stanzasPending)
				notify |= NSend;
		}
	}

	return doStep2(e);
}
