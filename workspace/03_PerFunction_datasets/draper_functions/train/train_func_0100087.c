CollectDistNames( CERTCertificate *cert, SECItem *k, void *data)
{
    CERTDistNames *names;
    PRBool saveit = PR_FALSE;
    CERTCertTrust trust;
    dnameNode *node;
    int len;

    names = (CERTDistNames *)data;

    if ( CERT_GetCertTrust(cert, &trust) == SECSuccess ) {

	if (  trust.sslFlags &  CERTDB_TRUSTED_CLIENT_CA )  {
	    saveit = PR_TRUE;
	}
    }

    if ( saveit ) {

	node = (dnameNode*)PORT_ArenaAlloc(names->arena, sizeof(dnameNode));
	if ( node == NULL ) {
	    return(SECFailure);
	}


	node->name.len = len = cert->derSubject.len;
	node->name.type = siBuffer;
	node->name.data = (unsigned char*)PORT_ArenaAlloc(names->arena, len);
	if ( node->name.data == NULL ) {
	    return(SECFailure);
	}
	PORT_Memcpy(node->name.data, cert->derSubject.data, len);


	node->next = (dnameNode *)names->head;
	names->head = (void *)node;


	names->nnames++;
    }

    return(SECSuccess);
}
