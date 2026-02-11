C_CloseAllSessions(CK_SLOT_ID slotID)
{
    size_t i;
    INIT_CONTEXT();

    st_logf("CloseAllSessions\n");

    for (i = 0; i < MAX_NUM_SESSION; i++)
	if (soft_token.state[i].session_handle != CK_INVALID_HANDLE)
	    close_session(&soft_token.state[i]);

    return CKR_OK;
}
