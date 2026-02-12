int parseLegacySyslogMsg(msg_t *pMsg, int flags)
{
	uchar *p2parse;
	int lenMsg;
	int i;
	uchar bufParseTAG[CONF_TAG_MAXSIZE];
	uchar bufParseHOSTNAME[CONF_HOSTNAME_MAXSIZE];
	BEGINfunc

	assert(pMsg != NULL);
	assert(pMsg->pszRawMsg != NULL);
	lenMsg = pMsg->iLenRawMsg - pMsg->offAfterPRI;
	p2parse = pMsg->pszRawMsg + pMsg->offAfterPRI;


	if(datetime.ParseTIMESTAMP3339(&(pMsg->tTIMESTAMP), &p2parse, &lenMsg) == RS_RET_OK) {
		;
	} else if(datetime.ParseTIMESTAMP3164(&(pMsg->tTIMESTAMP), &p2parse, &lenMsg) == RS_RET_OK) {
		;
	} else if(*p2parse == ' ' && lenMsg > 1) {
		++p2parse;
		--lenMsg;
		if(datetime.ParseTIMESTAMP3164(&(pMsg->tTIMESTAMP), &p2parse, &lenMsg) == RS_RET_OK) {

			;
		} else {


			--p2parse;
			++lenMsg;
		}
	}

	if(flags & IGNDATE) {

		memcpy(&pMsg->tTIMESTAMP, &pMsg->tRcvdAt, sizeof(struct syslogTime));
	}


	if(bParseHOSTNAMEandTAG && !(flags & INTERNAL_MSG)) {


		if(lenMsg > 0 && flags & PARSE_HOSTNAME) {
			i = 0;
			while(i < lenMsg && (isalnum(p2parse[i]) || p2parse[i] == '.' || p2parse[i] == '.'
				|| p2parse[i] == '_' || p2parse[i] == '-') && i < (CONF_HOSTNAME_MAXSIZE - 1)) {
				bufParseHOSTNAME[i] = p2parse[i];
				++i;
			}

			if(i == lenMsg) {


				p2parse += i;
				lenMsg -= i;
				bufParseHOSTNAME[i] = '\0';
				MsgSetHOSTNAME(pMsg, bufParseHOSTNAME, i);
			} else if(i > 0 && p2parse[i] == ' ' && isalnum(p2parse[i-1])) {

				p2parse += i + 1;
				lenMsg -= i + 1;
				bufParseHOSTNAME[i] = '\0';
				MsgSetHOSTNAME(pMsg, bufParseHOSTNAME, i);
			}
		}


		i = 0;
		while(lenMsg > 0 && *p2parse != ':' && *p2parse != ' ' && i < CONF_TAG_MAXSIZE) {
			bufParseTAG[i++] = *p2parse++;
			--lenMsg;
		}
		if(lenMsg > 0 && *p2parse == ':') {
			++p2parse;
			--lenMsg;
			bufParseTAG[i++] = ':';
		}


		bufParseTAG[i] = '\0';
		MsgSetTAG(pMsg, bufParseTAG, i);
	} else {


		if(!(flags & INTERNAL_MSG)) {
			DBGPRINTF("HOSTNAME and TAG not parsed by user configuraton.\n");
		}
	}


	MsgSetMSGoffs(pMsg, p2parse - pMsg->pszRawMsg);

	ENDfunc
	return 0;
}
