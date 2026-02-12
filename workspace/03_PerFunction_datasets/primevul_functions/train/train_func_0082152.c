auth_spa_server(auth_instance *ablock, uschar *data)
{
auth_spa_options_block *ob = (auth_spa_options_block *)(ablock->options_block);
uint8x lmRespData[24];
uint8x ntRespData[24];
SPAAuthRequest request;
SPAAuthChallenge challenge;
SPAAuthResponse  response;
SPAAuthResponse  *responseptr = &response;
uschar msgbuf[2048];
uschar *clearpass, *s;


if (!*data && auth_get_no64_data(&data, US"NTLM supported") != OK)
  return FAIL;

if (spa_base64_to_bits(CS &request, sizeof(request), CCS data) < 0)
  {
  DEBUG(D_auth) debug_printf("auth_spa_server(): bad base64 data in "
    "request: %s\n", data);
  return FAIL;
  }


spa_build_auth_challenge(&request, &challenge);
spa_bits_to_base64(msgbuf, US &challenge, spa_request_length(&challenge));

if (auth_get_no64_data(&data, msgbuf) != OK)
  return FAIL;


if (spa_base64_to_bits(CS &response, sizeof(response), CCS data) < 0)
  {
  DEBUG(D_auth) debug_printf("auth_spa_server(): bad base64 data in "
    "response: %s\n", data);
  return FAIL;
  }


  {
  int i;
  char * p = (CS responseptr) + IVAL(&responseptr->uUser.offset,0);
  int len = SVAL(&responseptr->uUser.len,0)/2;

  if (p + len*2 >= CS (responseptr+1))
    {
    DEBUG(D_auth)
      debug_printf("auth_spa_server(): bad uUser spec in response\n");
    return FAIL;
    }

  if (len + 1 >= sizeof(msgbuf)) return FAIL;
  for (i = 0; i < len; ++i)
    {
    msgbuf[i] = *p & 0x7f;
    p += 2;
    }
  msgbuf[i] = 0;
  }


auth_vars[0] = expand_nstring[1] = string_copy(msgbuf);
expand_nlength[1] = Ustrlen(msgbuf);
expand_nmax = 1;

debug_print_string(ablock->server_debug_string);


if (!(clearpass = expand_string(ob->spa_serverpassword)))
  if (f.expand_string_forcedfail)
    {
    DEBUG(D_auth) debug_printf("auth_spa_server(): forced failure while "
      "expanding spa_serverpassword\n");
    return FAIL;
    }
  else
    {
    DEBUG(D_auth) debug_printf("auth_spa_server(): error while expanding "
      "spa_serverpassword: %s\n", expand_string_message);
    return DEFER;
    }


spa_smb_encrypt(clearpass, challenge.challengeData, lmRespData);
spa_smb_nt_encrypt(clearpass, challenge.challengeData, ntRespData);


s = (US responseptr) + IVAL(&responseptr->ntResponse.offset,0);
if (s + 24 >= US (responseptr+1))
  {
  DEBUG(D_auth)
    debug_printf("auth_spa_server(): bad ntRespData spec in response\n");
  return FAIL;
  }

if (memcmp(ntRespData, s, 24) == 0)
  return auth_check_serv_cond(ablock);


return FAIL;
}
