CERT_EncodeAltNameExtension(PLArenaPool *arena,  CERTGeneralName  *value, SECItem *encodedValue)
{
    SECItem                **encodedGenName;
    SECStatus              rv = SECSuccess;

    encodedGenName = cert_EncodeGeneralNames(arena, value);
    if (SEC_ASN1EncodeItem (arena, encodedValue, &encodedGenName,
			    CERT_GeneralNamesTemplate) == NULL) {
	rv = SECFailure;
    }

    return rv;
}
