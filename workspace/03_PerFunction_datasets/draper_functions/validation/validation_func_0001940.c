PAM_conv (int num_msg,
                     const struct pam_message **msg,
                     struct pam_response **resp,
                     void *appdata_ptr) {
  int count;
  struct pam_response *reply;
  my_PAM *pam_config = (my_PAM *) appdata_ptr;


#define COPY_STRING(s) ((s) ? strdup(s) : NULL)

  reply = rad_malloc(num_msg * sizeof(struct pam_response));
  memset(reply, 0, num_msg * sizeof(struct pam_response));
  for (count = 0; count < num_msg; count++) {
    switch (msg[count]->msg_style) {
    case PAM_PROMPT_ECHO_ON:
      reply[count].resp_retcode = PAM_SUCCESS;
      reply[count].resp = COPY_STRING(pam_config->username);
      break;
    case PAM_PROMPT_ECHO_OFF:
      reply[count].resp_retcode = PAM_SUCCESS;
      reply[count].resp = COPY_STRING(pam_config->password);
      break;
    case PAM_TEXT_INFO:

      break;
    case PAM_ERROR_MSG:
    default:

      for (count = 0; count < num_msg; count++) {
        if (reply[count].resp) {

          memset(reply[count].resp, 0, strlen(reply[count].resp));
          free(reply[count].resp);
        }
      }
      free(reply);
      pam_config->error = 1;
      return PAM_CONV_ERR;
    }
  }
  *resp = reply;


  return PAM_SUCCESS;
}
