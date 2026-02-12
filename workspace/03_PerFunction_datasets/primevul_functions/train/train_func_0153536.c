auth_call_pam(const uschar *s, uschar **errptr)
{
pam_handle_t *pamh = NULL;
struct pam_conv pamc;
int pam_error;
int sep = 0;
uschar *user;


pamc.conv = pam_converse;
pamc.appdata_ptr = NULL;


pam_args = s;
pam_conv_had_error = FALSE;
pam_arg_ended = FALSE;


user = string_nextinlist(&pam_args, &sep, NULL, 0);
if (user == NULL || user[0] == 0) return FAIL;


DEBUG(D_auth)
  debug_printf("Running PAM authentication for user \"%s\"\n", user);

pam_error = pam_start ("exim", CS user, &pamc, &pamh);


if (pam_error == PAM_SUCCESS)
  {
  pam_error = pam_authenticate (pamh, PAM_SILENT);
  if (pam_error == PAM_SUCCESS && !pam_conv_had_error)
    pam_error = pam_acct_mgmt (pamh, PAM_SILENT);
  }


pam_end(pamh, PAM_SUCCESS);


if (pam_error == PAM_SUCCESS)
  {
  DEBUG(D_auth) debug_printf("PAM success\n");
  return OK;
  }

*errptr = US pam_strerror(pamh, pam_error);
DEBUG(D_auth) debug_printf("PAM error: %s\n", *errptr);

if (pam_error == PAM_USER_UNKNOWN ||
    pam_error == PAM_AUTH_ERR ||
    pam_error == PAM_ACCT_EXPIRED)
  return FAIL;

return ERROR;
}
