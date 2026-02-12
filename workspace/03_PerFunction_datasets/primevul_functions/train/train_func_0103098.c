auth_spa_client(
  auth_instance *ablock,
  void * sx,
  int timeout,
  uschar *buffer,
  int buffsize)
{
auth_spa_options_block *ob =
       (auth_spa_options_block *)(ablock->options_block);
SPAAuthRequest   request;
SPAAuthChallenge challenge;
SPAAuthResponse  response;
char msgbuf[2048];
char *domain = NULL;
char *username, *password;


*buffer = 0;

if (!(username = CS expand_string(ob->spa_username)))
  {
  if (f.expand_string_forcedfail) return CANCELLED;
  string_format(buffer, buffsize, "expansion of \"%s\" failed in %s "
   "authenticator: %s", ob->spa_username, ablock->name,
   expand_string_message);
  return ERROR;
  }

if (!(password = CS expand_string(ob->spa_password)))
  {
  if (f.expand_string_forcedfail) return CANCELLED;
  string_format(buffer, buffsize, "expansion of \"%s\" failed in %s "
   "authenticator: %s", ob->spa_password, ablock->name,
   expand_string_message);
  return ERROR;
  }

if (ob->spa_domain)
  if (!(domain = CS expand_string(ob->spa_domain)))
    {
    if (f.expand_string_forcedfail) return CANCELLED;
    string_format(buffer, buffsize, "expansion of \"%s\" failed in %s "
		  "authenticator: %s", ob->spa_domain, ablock->name,
		  expand_string_message);
    return ERROR;
    }


if (smtp_write_command(sx, SCMD_FLUSH, "AUTH %s\r\n", ablock->public_name) < 0)
  return FAIL_SEND;


if (!smtp_read_response(sx, US buffer, buffsize, '3', timeout))
  return FAIL;

DSPA("\n\n%s authenticator: using domain %s\n\n", ablock->name, domain);

spa_build_auth_request(&request, CS username, domain);
spa_bits_to_base64(US msgbuf, US &request, spa_request_length(&request));

DSPA("\n\n%s authenticator: sending request (%s)\n\n", ablock->name, msgbuf);


if (smtp_write_command(sx, SCMD_FLUSH, "%s\r\n", msgbuf) < 0)
  return FAIL_SEND;


if (!smtp_read_response(sx, US buffer, buffsize, '3', timeout))
  return FAIL;


DSPA("\n\n%s authenticator: challenge (%s)\n\n", ablock->name, buffer + 4);
spa_base64_to_bits(CS (&challenge), sizeof(challenge), CCS (buffer + 4));

spa_build_auth_response(&challenge, &response, CS username, CS password);
spa_bits_to_base64(US msgbuf, US &response, spa_request_length(&response));
DSPA("\n\n%s authenticator: challenge response (%s)\n\n", ablock->name, msgbuf);


if (smtp_write_command(sx, SCMD_FLUSH, "%s\r\n", msgbuf) < 0)
       return FAIL_SEND;


if (smtp_read_response(sx, US buffer, buffsize, '2', timeout))
  return OK;


if (errno != 0 || buffer[0] != '3')
  return FAIL;

return FAIL;
}
