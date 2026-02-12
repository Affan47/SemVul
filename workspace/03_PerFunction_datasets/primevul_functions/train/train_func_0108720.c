finish_check_padata(struct padata_state *state, krb5_error_code code)
{
    kdc_preauth_respond_fn respond;
    void *arg;

    if (state->pa_ok || !state->pa_found) {


        code = 0;
        goto cleanup;
    }


    if (maybe_add_etype_info2(state, code) != 0) {
        code = KRB5KDC_ERR_PREAUTH_FAILED;
        goto cleanup;
    }


    *state->e_data_out = state->pa_e_data;
    *state->typed_e_data_out = state->typed_e_data_flag;
    state->pa_e_data = NULL;

cleanup:


    respond = state->respond;
    arg = state->arg;
    krb5_free_pa_data(state->context, state->pa_e_data);
    free(state);
    (*respond)(arg, filter_preauth_error(code));
}
