AC_DIGEST_new(void)
{
  AC_DIGEST *ret = NULL;
  ASN1_CTX c;

  M_ASN1_New_Malloc(ret, AC_DIGEST);
  M_ASN1_New(ret->type, M_ASN1_ENUMERATED_new);
  ret->oid = NULL;
  ret->algor = NULL;
  M_ASN1_New(ret->algor,  X509_ALGOR_new);
  M_ASN1_New(ret->digest, M_ASN1_BIT_STRING_new);
  return(ret);
  M_ASN1_New_Error(AC_F_AC_DIGEST_New);
}
