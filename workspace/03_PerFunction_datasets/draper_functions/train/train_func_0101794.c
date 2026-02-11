setSubjectKeyIdentifier( UINT8* a_value, UINT32 a_valueLen )
{
    SINT32 ret = E_UNKNOWN;
    ASN1_OCTET_STRING* skid = NULL;

    skid = ASN1_OCTET_STRING_new();
    if(NULL == skid)   goto end;

    ASN1_OCTET_STRING_set(skid, a_value, a_valueLen);
    if( X509_add1_ext_i2d(m_pCert, NID_subject_key_identifier, skid, false, X509V3_ADD_REPLACE) == 1)
        ret = E_SUCCESS;

end:
    ASN1_OCTET_STRING_free(skid);
    return ret;
}
