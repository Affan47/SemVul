static void tryEmulateAPPNAME(msg_t *pM)
{
	assert(pM != NULL);
	if(pM->pCSAPPNAME != NULL)
		return;

	if(getProtocolVersion(pM) == 0) {

		MsgSetAPPNAME(pM, (char*)getProgramName(pM, MUTEX_ALREADY_LOCKED));
	}
}
