CURLcode Curl_ntlm_core_mk_ntlmv2_resp(unsigned char *ntlmv2hash,
                                       unsigned char *challenge_client,
                                       struct ntlmdata *ntlm,
                                       unsigned char **ntresp,
                                       unsigned int *ntresp_len)
{


  unsigned int len = 0;
  unsigned char *ptr = NULL;
  unsigned char hmac_output[NTLM_HMAC_MD5_LEN];
  curl_off_t tw;

  CURLcode result = CURLE_OK;

#if CURL_SIZEOF_CURL_OFF_T < 8
#error "this section needs 64bit support to work"
#endif


#ifdef DEBUGBUILD
  char *force_timestamp = getenv("CURL_FORCETIME");
  if(force_timestamp)
    tw = CURL_OFF_T_C(11644473600) * 10000000;
  else
#endif
    tw = ((curl_off_t)time(NULL) + CURL_OFF_T_C(11644473600)) * 10000000;


  len = NTLM_HMAC_MD5_LEN + NTLMv2_BLOB_LEN;


  ptr = calloc(1, len);
  if(!ptr)
    return CURLE_OUT_OF_MEMORY;


  snprintf((char *)ptr + NTLM_HMAC_MD5_LEN, NTLMv2_BLOB_LEN,
           "%c%c%c%c"
           "%c%c%c%c",
           NTLMv2_BLOB_SIGNATURE[0], NTLMv2_BLOB_SIGNATURE[1],
           NTLMv2_BLOB_SIGNATURE[2], NTLMv2_BLOB_SIGNATURE[3],
           0, 0, 0, 0);

  Curl_write64_le(tw, ptr + 24);
  memcpy(ptr + 32, challenge_client, 8);
  memcpy(ptr + 44, ntlm->target_info, ntlm->target_info_len);


  memcpy(ptr + 8, &ntlm->nonce[0], 8);
  result = Curl_hmac_md5(ntlmv2hash, NTLM_HMAC_MD5_LEN, ptr + 8,
                         NTLMv2_BLOB_LEN + 8, hmac_output);
  if(result) {
    free(ptr);
    return result;
  }


  memcpy(ptr, hmac_output, NTLM_HMAC_MD5_LEN);


  *ntresp = ptr;
  *ntresp_len = len;

  return result;
}
