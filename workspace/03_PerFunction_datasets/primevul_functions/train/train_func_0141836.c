AuthenticodeVerify (
  IN  CONST UINT8  *AuthData,
  IN  UINTN        DataSize,
  IN  CONST UINT8  *TrustedCert,
  IN  UINTN        CertSize,
  IN  CONST UINT8  *ImageHash,
  IN  UINTN        HashSize
  )
{
  BOOLEAN      Status;
  PKCS7        *Pkcs7;
  CONST UINT8  *Temp;
  CONST UINT8  *OrigAuthData;
  UINT8        *SpcIndirectDataContent;
  UINT8        Asn1Byte;
  UINTN        ContentSize;
  CONST UINT8  *SpcIndirectDataOid;


  if ((AuthData == NULL) || (TrustedCert == NULL) || (ImageHash == NULL)) {
    return FALSE;
  }

  if ((DataSize > INT_MAX) || (CertSize > INT_MAX) || (HashSize > INT_MAX)) {
    return FALSE;
  }

  Status       = FALSE;
  Pkcs7        = NULL;
  OrigAuthData = AuthData;


  Temp  = AuthData;
  Pkcs7 = d2i_PKCS7 (NULL, &Temp, (int)DataSize);
  if (Pkcs7 == NULL) {
    goto _Exit;
  }


  if (!PKCS7_type_is_signed (Pkcs7) || PKCS7_get_detached (Pkcs7)) {
    goto _Exit;
  }


  SpcIndirectDataOid = OBJ_get0_data(Pkcs7->d.sign->contents->type);
  if (OBJ_length(Pkcs7->d.sign->contents->type) != sizeof(mSpcIndirectOidValue) ||
      CompareMem (
        SpcIndirectDataOid,
        mSpcIndirectOidValue,
        sizeof (mSpcIndirectOidValue)
        ) != 0) {


    goto _Exit;
  }


  SpcIndirectDataContent = (UINT8 *)(Pkcs7->d.sign->contents->d.other->value.asn1_string->data);


  Asn1Byte = *(SpcIndirectDataContent + 1);

  if ((Asn1Byte & 0x80) == 0) {


    ContentSize = (UINTN) (Asn1Byte & 0x7F);


    SpcIndirectDataContent += 2;

  } else if ((Asn1Byte & 0x81) == 0x81) {


    ContentSize = (UINTN) (*(UINT8 *)(SpcIndirectDataContent + 2));


    SpcIndirectDataContent += 3;

  } else if ((Asn1Byte & 0x82) == 0x82) {


    ContentSize = (UINTN) (*(UINT8 *)(SpcIndirectDataContent + 2));
    ContentSize = (ContentSize << 8) + (UINTN)(*(UINT8 *)(SpcIndirectDataContent + 3));


    SpcIndirectDataContent += 4;

  } else {
    goto _Exit;
  }


  if (CompareMem (SpcIndirectDataContent + ContentSize - HashSize, ImageHash, HashSize) != 0) {


    goto _Exit;
  }


  Status = (BOOLEAN) Pkcs7Verify (OrigAuthData, DataSize, TrustedCert, CertSize, SpcIndirectDataContent, ContentSize);

_Exit:


  PKCS7_free (Pkcs7);

  return Status;
}
