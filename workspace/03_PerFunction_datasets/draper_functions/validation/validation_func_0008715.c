nssCryptokiTrust_GetAttributes (
  nssCryptokiObject *trustObject,
  nssSession *sessionOpt,
  NSSItem *sha1_hash,
  nssTrustLevel *serverAuth,
  nssTrustLevel *clientAuth,
  nssTrustLevel *codeSigning,
  nssTrustLevel *emailProtection,
  PRBool *stepUpApproved
)
{
    PRStatus status;
    NSSSlot *slot;
    nssSession *session;
    CK_BBOOL isToken = PR_FALSE;
    CK_BBOOL stepUp = PR_FALSE;
    CK_TRUST saTrust = CKT_NSS_TRUST_UNKNOWN;
    CK_TRUST caTrust = CKT_NSS_TRUST_UNKNOWN;
    CK_TRUST epTrust = CKT_NSS_TRUST_UNKNOWN;
    CK_TRUST csTrust = CKT_NSS_TRUST_UNKNOWN;
    CK_ATTRIBUTE_PTR attr;
    CK_ATTRIBUTE trust_template[7];
    CK_ATTRIBUTE_PTR sha1_hash_attr;
    CK_ULONG trust_size;


    NSS_CK_TEMPLATE_START(trust_template, attr, trust_size);
    NSS_CK_SET_ATTRIBUTE_VAR(attr, CKA_TOKEN,                  isToken);
    NSS_CK_SET_ATTRIBUTE_VAR(attr, CKA_TRUST_SERVER_AUTH,      saTrust);
    NSS_CK_SET_ATTRIBUTE_VAR(attr, CKA_TRUST_CLIENT_AUTH,      caTrust);
    NSS_CK_SET_ATTRIBUTE_VAR(attr, CKA_TRUST_EMAIL_PROTECTION, epTrust);
    NSS_CK_SET_ATTRIBUTE_VAR(attr, CKA_TRUST_CODE_SIGNING,     csTrust);
    NSS_CK_SET_ATTRIBUTE_VAR(attr, CKA_TRUST_STEP_UP_APPROVED, stepUp);
    sha1_hash_attr = attr;
    NSS_CK_SET_ATTRIBUTE_ITEM(attr, CKA_CERT_SHA1_HASH,     sha1_hash);
    NSS_CK_TEMPLATE_FINISH(trust_template, attr, trust_size);

    status = nssToken_GetCachedObjectAttributes(trustObject->token, NULL,
                                                trustObject,
                                                CKO_NSS_TRUST,
                                                trust_template, trust_size);
    if (status != PR_SUCCESS) {
	session = sessionOpt ?
	          sessionOpt :
	          nssToken_GetDefaultSession(trustObject->token);
	if (!session) {
	    nss_SetError(NSS_ERROR_INVALID_ARGUMENT);
	    return PR_FAILURE;
	}

	slot = nssToken_GetSlot(trustObject->token);
	status = nssCKObject_GetAttributes(trustObject->handle,
	                                   trust_template, trust_size,
	                                   NULL, session, slot);
	nssSlot_Destroy(slot);
	if (status != PR_SUCCESS) {
	    return status;
	}
    }

    if (sha1_hash_attr->ulValueLen == -1) {

	sha1_hash_attr->ulValueLen = 0;
    }
    sha1_hash->size = sha1_hash_attr->ulValueLen;
    *serverAuth = get_nss_trust(saTrust);
    *clientAuth = get_nss_trust(caTrust);
    *emailProtection = get_nss_trust(epTrust);
    *codeSigning = get_nss_trust(csTrust);
    *stepUpApproved = stepUp;
    return PR_SUCCESS;
}
