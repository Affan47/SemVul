ParseMsg(smsg_t *pMsg)
{
	rsRetVal localRet = RS_RET_ERR;
	parserList_t *pParserList;
	parser_t *pParser;
	sbool bIsSanitized;
	sbool bPRIisParsed;
	static int iErrMsgRateLimiter = 0;
	DEFiRet;

	if(pMsg->iLenRawMsg == 0)
		ABORT_FINALIZE(RS_RET_EMPTY_MSG);

	CHKiRet(uncompressMessage(pMsg));


	DBGPRINTF("msg parser: flags %x, from '%s', msg '%.60s'\n", pMsg->msgFlags,
		  (pMsg->msgFlags & NEEDS_DNSRESOL) ? UCHAR_CONSTANT("~NOTRESOLVED~") : getRcvFrom(pMsg),
		  pMsg->pszRawMsg);


	pParserList = ruleset.GetParserList(ourConf, pMsg);
	if(pParserList == NULL) {
		pParserList = pDfltParsLst;
	}
	DBGPRINTF("parse using parser list %p%s.\n", pParserList,
		  (pParserList == pDfltParsLst) ? " (the default list)" : "");

	bIsSanitized = RSFALSE;
	bPRIisParsed = RSFALSE;
	while(pParserList != NULL) {
		pParser = pParserList->pParser;
		if(pParser->bDoSanitazion && bIsSanitized == RSFALSE) {
			CHKiRet(SanitizeMsg(pMsg));
			if(pParser->bDoPRIParsing && bPRIisParsed == RSFALSE) {
				CHKiRet(ParsePRI(pMsg));
				bPRIisParsed = RSTRUE;
			}
			bIsSanitized = RSTRUE;
		}
		if(pParser->pModule->mod.pm.parse2 == NULL)
			localRet = pParser->pModule->mod.pm.parse(pMsg);
		else
			localRet = pParser->pModule->mod.pm.parse2(pParser->pInst, pMsg);
		DBGPRINTF("Parser '%s' returned %d\n", pParser->pName, localRet);
		if(localRet != RS_RET_COULD_NOT_PARSE)
			break;
		pParserList = pParserList->pNext;
	}


	if(localRet != RS_RET_OK) {
		if(++iErrMsgRateLimiter > 1000) {
			errmsg.LogError(0, localRet, "Error: one message could not be processed by "
			 	"any parser, message is being discarded (start of raw msg: '%.50s')",
				pMsg->pszRawMsg);
		}
		DBGPRINTF("No parser could process the message (state %d), we need to discard it.\n", localRet);
		ABORT_FINALIZE(localRet);
	}


	pMsg->msgFlags &= ~NEEDS_PARSING;

finalize_it:
	RETiRet;
}
