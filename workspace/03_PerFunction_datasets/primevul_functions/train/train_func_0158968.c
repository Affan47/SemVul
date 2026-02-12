rsRetVal msgConstruct(msg_t **ppThis)
{
	DEFiRet;

	CHKiRet(msgBaseConstruct(ppThis));


	datetime.getCurrTime(&((*ppThis)->tRcvdAt), &((*ppThis)->ttGenTime));
	memcpy(&(*ppThis)->tTIMESTAMP, &(*ppThis)->tRcvdAt, sizeof(struct syslogTime));

finalize_it:
	RETiRet;
}
