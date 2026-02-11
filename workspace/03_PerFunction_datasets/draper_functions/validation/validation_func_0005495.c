ssl3_GetSessionTicketKeysPKCS11(sslSocket *ss, PK11SymKey **aes_key,
                                PK11SymKey **mac_key)
{
    if (PR_CallOnceWithArg(&generate_session_keys_once,
	    ssl3_GenerateSessionTicketKeysPKCS11, ss) != PR_SUCCESS)
	return SECFailure;

    if (session_ticket_enc_key_pkcs11 == NULL ||
	session_ticket_mac_key_pkcs11 == NULL)
	return SECFailure;

    *aes_key = session_ticket_enc_key_pkcs11;
    *mac_key = session_ticket_mac_key_pkcs11;
    return SECSuccess;
}
