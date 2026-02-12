static bool encrypt_des(const unsigned char *in, unsigned char *out,
                        const unsigned char *key_56)
{
  HCRYPTPROV hprov;
  HCRYPTKEY hkey;
  struct {
    BLOBHEADER hdr;
    unsigned int len;
    char key[8];
  } blob;
  DWORD len = 8;


  if(!CryptAcquireContext(&hprov, NULL, NULL, PROV_RSA_FULL,
                          CRYPT_VERIFYCONTEXT))
    return FALSE;


  memset(&blob, 0, sizeof(blob));
  blob.hdr.bType = PLAINTEXTKEYBLOB;
  blob.hdr.bVersion = 2;
  blob.hdr.aiKeyAlg = CALG_DES;
  blob.len = sizeof(blob.key);


  extend_key_56_to_64(key_56, blob.key);


  Curl_des_set_odd_parity((unsigned char *) blob.key, sizeof(blob.key));


  if(!CryptImportKey(hprov, (BYTE *) &blob, sizeof(blob), 0, 0, &hkey)) {
    CryptReleaseContext(hprov, 0);

    return FALSE;
  }

  memcpy(out, in, 8);


  CryptEncrypt(hkey, 0, FALSE, 0, out, &len, len);

  CryptDestroyKey(hkey);
  CryptReleaseContext(hprov, 0);

  return TRUE;
}
