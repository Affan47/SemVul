smtp_in_auth(auth_instance *au, uschar ** s, uschar ** ss)
{
const uschar *set_id = NULL;
int rc, i;


for (i = 0; i < AUTH_VARS; i++) auth_vars[i] = NULL;
expand_nmax = 0;
expand_nlength[0] = 0;

rc = (au->info->servercode)(au, smtp_cmd_data);
if (au->set_id) set_id = expand_string(au->set_id);
expand_nmax = -1;
for (i = 0; i < AUTH_VARS; i++) auth_vars[i] = NULL;


if (set_id) set_id = string_printing(set_id);


if (rc != OK)
  set_id = set_id && *set_id
    ? string_sprintf(" (set_id=%s)", set_id) : US"";


switch(rc)
  {
  case OK:
  if (!au->set_id || set_id)
    {
    if (set_id) authenticated_id = string_copy_malloc(set_id);
    sender_host_authenticated = au->name;
    sender_host_auth_pubname  = au->public_name;
    authentication_failed = FALSE;
    authenticated_fail_id = NULL;

    received_protocol =
      (sender_host_address ? protocols : protocols_local)
	[pextend + pauthed + (tls_in.active.sock >= 0 ? pcrpted:0)];
    *s = *ss = US"235 Authentication succeeded";
    authenticated_by = au;
    break;
    }


  auth_defer_msg = expand_string_message;


  case DEFER:
  if (set_id) authenticated_fail_id = string_copy_malloc(set_id);
  *s = string_sprintf("435 Unable to authenticate at present%s",
    auth_defer_user_msg);
  *ss = string_sprintf("435 Unable to authenticate at present%s: %s",
    set_id, auth_defer_msg);
  break;

  case BAD64:
  *s = *ss = US"501 Invalid base64 data";
  break;

  case CANCELLED:
  *s = *ss = US"501 Authentication cancelled";
  break;

  case UNEXPECTED:
  *s = *ss = US"553 Initial data not expected";
  break;

  case FAIL:
  if (set_id) authenticated_fail_id = string_copy_malloc(set_id);
  *s = US"535 Incorrect authentication data";
  *ss = string_sprintf("535 Incorrect authentication data%s", set_id);
  break;

  default:
  if (set_id) authenticated_fail_id = string_copy_malloc(set_id);
  *s = US"435 Internal error";
  *ss = string_sprintf("435 Internal error%s: return %d from authentication "
    "check", set_id, rc);
  break;
  }

return rc;
}
