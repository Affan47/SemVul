pass_conv(int num_msg, const struct pam_message **msgm UNUSED,
          struct pam_response **response, void *appdata_ptr)
{
    int i;

    *response = malloc(num_msg * sizeof(struct pam_response));
    if (*response == NULL)
        return PAM_CONV_ERR;
    for (i = 0; i < num_msg; i++) {
        (*response)[i].resp = strdup((char *)appdata_ptr);
        (*response)[i].resp_retcode = 0;
    }
    return PAM_SUCCESS;
}
