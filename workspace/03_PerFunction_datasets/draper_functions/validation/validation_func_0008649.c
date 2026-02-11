DisconnectAllClients(GRPENT *pGE, char *message)
#else
DisconnectAllClients(pGE, message)
    GRPENT *pGE;
    char *message;
#endif
{
    CONSCLIENT *pCL;

    if ((GRPENT *)0 == pGE) {
	return;
    }

    for (pCL = pGE->pCLall; (CONSCLIENT *)0 != pCL; pCL = pCL->pCLscan) {
	DisconnectClient(pGE, pCL, message, FLAGTRUE);
    }
}
