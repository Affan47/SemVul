sec_pkcs7_decoder_get_recipient_key (SEC_PKCS7DecoderContext *p7dcx,
				     SEC_PKCS7RecipientInfo **recipientinfos,
				     SEC_PKCS7EncryptedContentInfo *enccinfo)
{
    SEC_PKCS7RecipientInfo *ri;
    CERTCertificate *cert = NULL;
    SECKEYPrivateKey *privkey = NULL;
    PK11SymKey *bulkkey = NULL;
    SECOidTag keyalgtag, bulkalgtag, encalgtag;
    PK11SlotInfo *slot = NULL;

    if (recipientinfos == NULL || recipientinfos[0] == NULL) {
	p7dcx->error = SEC_ERROR_NOT_A_RECIPIENT;
	goto no_key_found;
    }

    cert = PK11_FindCertAndKeyByRecipientList(&slot,recipientinfos,&ri,
						&privkey, p7dcx->pwfn_arg);
    if (cert == NULL) {
	p7dcx->error = SEC_ERROR_NOT_A_RECIPIENT;
	goto no_key_found;
    }

    ri->cert = cert;
    PORT_Assert(privkey != NULL);

    keyalgtag = SECOID_GetAlgorithmTag(&(cert->subjectPublicKeyInfo.algorithm));
    encalgtag = SECOID_GetAlgorithmTag (&(ri->keyEncAlg));
    if (keyalgtag != encalgtag) {
	p7dcx->error = SEC_ERROR_PKCS7_KEYALG_MISMATCH;
	goto no_key_found;
    }
    bulkalgtag = SECOID_GetAlgorithmTag (&(enccinfo->contentEncAlg));

    switch (encalgtag) {
      case SEC_OID_PKCS1_RSA_ENCRYPTION:
	bulkkey = PK11_PubUnwrapSymKey (privkey, &ri->encKey,
					PK11_AlgtagToMechanism (bulkalgtag),
					CKA_DECRYPT, 0);
	if (bulkkey == NULL) {
	    p7dcx->error = PORT_GetError();
	    PORT_SetError(0);
	    goto no_key_found;
	}
	break;
      default:
	p7dcx->error = SEC_ERROR_UNSUPPORTED_KEYALG;
	break;
    }

no_key_found:
    if (privkey != NULL)
	SECKEY_DestroyPrivateKey (privkey);
    if (slot != NULL)
	PK11_FreeSlot(slot);

    return bulkkey;
}
