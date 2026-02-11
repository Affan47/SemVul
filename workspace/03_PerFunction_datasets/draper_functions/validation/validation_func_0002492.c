JAR_fetch_cert(long length, void *key)
{
    CERTIssuerAndSN issuerSN;
    CERTCertificate *cert = NULL;
    CERTCertDBHandle *certdb;

    certdb = JAR_open_database();
    if (certdb) {
	unsigned char *keyData = (unsigned char *)key;
	issuerSN.derIssuer.len = (keyData[0] << 8) + keyData[0];
	issuerSN.derIssuer.data = &keyData[2];
	issuerSN.serialNumber.len = length - (2 + issuerSN.derIssuer.len);
	issuerSN.serialNumber.data = &keyData[2+issuerSN.derIssuer.len];
	cert = CERT_FindCertByIssuerAndSN (certdb, &issuerSN);
	JAR_close_database (certdb);
    }
    return cert;
}
