static bool encrypt_des(const unsigned char *in, unsigned char *out,
                        const unsigned char *key_56)
{
  const CK_MECHANISM_TYPE mech = CKM_DES_ECB;
  PK11SlotInfo *slot = NULL;
  char key[8];
  SECItem key_item;
  PK11SymKey *symkey = NULL;
  SECItem *param = NULL;
  PK11Context *ctx = NULL;
  int out_len;
  bool rv = FALSE;


  slot = PK11_GetInternalKeySlot();
  if(!slot)
    return FALSE;


  extend_key_56_to_64(key_56, key);


  Curl_des_set_odd_parity((unsigned char *) key, sizeof(key));


  key_item.data = (unsigned char *)key;
  key_item.len = sizeof(key);
  symkey = PK11_ImportSymKey(slot, mech, PK11_OriginUnwrap, CKA_ENCRYPT,
                             &key_item, NULL);
  if(!symkey)
    goto fail;


  param = PK11_ParamFromIV(mech,  NULL);
  if(!param)
    goto fail;
  ctx = PK11_CreateContextBySymKey(mech, CKA_ENCRYPT, symkey, param);
  if(!ctx)
    goto fail;


  if(SECSuccess == PK11_CipherOp(ctx, out, &out_len,  8,
                                 (unsigned char *)in,  8)
      && SECSuccess == PK11_Finalize(ctx))
    rv =  TRUE;

fail:

  if(ctx)
    PK11_DestroyContext(ctx, PR_TRUE);
  if(symkey)
    PK11_FreeSymKey(symkey);
  if(param)
    SECITEM_FreeItem(param, PR_TRUE);
  PK11_FreeSlot(slot);
  return rv;
}
