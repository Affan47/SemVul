completeKey(const PKCS11Object &cert)
{

    bool modulusExists, exponentExists;
    CKYBuffer modulus; CKYBuffer_InitEmpty(&modulus);
    CKYBuffer exponent; CKYBuffer_InitEmpty(&exponent);

    if (!attributeExists(CKA_LABEL)) {
	setAttribute(CKA_LABEL, cert.getAttribute(CKA_LABEL));
    }
    try {
 	modulusExists = attributeExists(CKA_MODULUS);
	exponentExists = attributeExists(CKA_PUBLIC_EXPONENT);
	if (!modulusExists || !exponentExists) {
	    const CKYBuffer *key = cert.getPubKey();
	    GetKeyFields(key, &modulus, &exponent);
	    if (!modulusExists) {
		setAttribute(CKA_MODULUS, &modulus);
	    }
	    if (!exponentExists) {
		setAttribute(CKA_PUBLIC_EXPONENT, &exponent);
	    }
	}
    } catch (PKCS11Exception &e) {
	CKYBuffer_FreeData(&modulus);
	CKYBuffer_FreeData(&exponent);
	throw e;
    }
    CKYBuffer_FreeData(&modulus);
    CKYBuffer_FreeData(&exponent);
}
