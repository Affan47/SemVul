MagickPrivate void SetSignatureDigest(SignatureInfo *signature_info,
  const StringInfo *digest)
{


  assert(signature_info != (SignatureInfo *) NULL);
  assert(signature_info->signature == MagickCoreSignature);
  SetStringInfo(signature_info->digest,digest);
}
