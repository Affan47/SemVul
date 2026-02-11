dsgw_encDec(CK_ATTRIBUTE_TYPE operation, const char *msg)
{
  CK_MECHANISM_TYPE type = CKM_RC4;
  PK11SlotInfo *slot = 0;
  PK11SymKey *key = 0;
  SECItem *params = 0;
  PK11Context *context = 0;
  unsigned char *output;
  unsigned char *input;
  char *edStr;
  int outLen;
  unsigned int len;
  SECStatus s;
  SECItem keyItem = { siBuffer, dsgw_tmmdi, sizeof dsgw_tmmdi };
  int noGood = 0;
  unsigned int inlen;

  if (msg == NULL) {
    return NULL;
  }

  if (*msg == '\0') {
    return PL_strdup(msg);
  }

  if (operation == CKA_DECRYPT) {
    input = ATOB_AsciiToData(msg, &inlen);
    if (msg == NULL)
      return NULL;
  } else {
    inlen = PL_strlen(msg);
    input = (unsigned char *) msg;
  }

  output = (unsigned char *) malloc(inlen + 65);
  if (output == NULL) {
    return NULL;
  }


  dsgw_initNSS();


  slot = PK11_GetInternalKeySlot();
  if (!slot)
  {
    noGood = 1;
    goto dsgw_encDec_done;
  }


  key = PK11_ImportSymKey(slot, CKM_RC4, PK11_OriginGenerated, operation, &keyItem, 0);


  params = PK11_GenerateNewParam(type, key);
  if (!params)
  {
    noGood = 1;
    goto dsgw_encDec_done;
  }


  context = PK11_CreateContextBySymKey(type, operation, key, params);
  if (!context)
  {
    noGood = 1;
    goto dsgw_encDec_done;
  }


  s = PK11_CipherOp(context, output, &outLen, inlen + 64, input, (int) inlen);
  if (s != SECSuccess)
  {
    noGood = 1;
    goto dsgw_encDec_done;
  }


  s = PK11_DigestFinal(context, &output[outLen], &len, sizeof output - outLen);
  if (s != SECSuccess)
  {
    noGood = 1;
    goto dsgw_encDec_done;
  }


  outLen += len;


  PK11_Finalize(context);


  PK11_DestroyContext(context, PR_TRUE);
  context = 0;

dsgw_encDec_done:
  if (context) PK11_DestroyContext(context, PR_TRUE);
  if (params) SECITEM_ZfreeItem(params, PR_TRUE);
  if (key) PK11_FreeSymKey(key);
  if (slot) PK11_FreeSlot(slot);

  if (noGood == 1) {
    return(NULL);
  }

  if (operation == CKA_DECRYPT) {
    edStr = (char *) output;
    edStr[outLen] = '\0';
  } else {
    edStr = BTOA_DataToAscii(output, outLen);
    free(output);
  }

  return(edStr);
}
