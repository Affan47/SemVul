destructSess(ptcpsess_t *pSess)
{
	free(pSess->pMsg);
	free(pSess->epd);
	prop.Destruct(&pSess->peerName);
	prop.Destruct(&pSess->peerIP);

	pSess->pMsg = NULL;
	pSess->epd = NULL;
	free(pSess);
}
