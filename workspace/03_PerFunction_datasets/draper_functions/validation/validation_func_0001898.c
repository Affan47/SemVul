store(CK_SESSION_HANDLE ulSessionHandle, CK_OBJECT_HANDLE ulObjectHandle)
{
	const CK_RV rv = Pkcs11::m_p11->C_SetAttributeValue(ulSessionHandle, ulObjectHandle, &m_Attr, 1);
	if (rv != CKR_OK)
		Pkcs11::pk11error("C_SetAttributeValue", rv);
}
