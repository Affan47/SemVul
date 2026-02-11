answer_pam_message (int                        num_msg,
                    const struct pam_message **msg,
                    struct pam_response      **resp,
                    void                      *appdata_ptr)
{
        int i;
        struct pam_response *resps;


        resps = malloc((sizeof (struct pam_response)) * num_msg);


        for (i = 0; i < num_msg; i++) {
                if ((*msg)[i].msg_style == PAM_PROMPT_ECHO_OFF) {
                        const char *message = (*msg)[i].msg;

                        if (old_password && strstr(message, "current") != NULL)
                                resps[i].resp = strdup(old_password);
                        else if (strcmp(message, "PIN") == 0)
                                resps[i].resp = pin ? strdup(pin) : NULL;
                        else
                                resps[i].resp = strdup(password);
                } else {
                        resps[i].resp = NULL;
                }

                resps[i].resp_retcode = 0;

        }

        *resp = resps;

        return PAM_SUCCESS;
}
