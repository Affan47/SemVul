do_trans (int sock, gss_ctx_id_t context_hdl)
{
    OM_uint32 maj_stat, min_stat;
    gss_buffer_desc real_input_token, real_output_token;
    gss_buffer_t input_token = &real_input_token,
	output_token = &real_output_token;
    int conf_flag;


    input_token->length = 3;
    input_token->value  = strdup("hej");

    maj_stat = gss_get_mic(&min_stat,
			   context_hdl,
			   GSS_C_QOP_DEFAULT,
			   input_token,
			   output_token);
    if (GSS_ERROR(maj_stat))
	gss_err (1, min_stat, "gss_get_mic");

    write_token (sock, input_token);
    write_token (sock, output_token);

    gss_release_buffer(&min_stat, output_token);


    read_token (sock, input_token);
    read_token (sock, output_token);

    maj_stat = gss_verify_mic(&min_stat,
			      context_hdl,
			      input_token,
			      output_token,
			      NULL);
    if (GSS_ERROR(maj_stat))
	gss_err (1, min_stat, "gss_verify_mic");

    gss_release_buffer (&min_stat, input_token);
    gss_release_buffer (&min_stat, output_token);


    input_token->length = 7;
    input_token->value  = "hemligt";

    maj_stat = gss_wrap (&min_stat,
			 context_hdl,
			 0,
			 GSS_C_QOP_DEFAULT,
			 input_token,
			 NULL,
			 output_token);
    if (GSS_ERROR(maj_stat))
	gss_err (1, min_stat, "gss_wrap");

    write_token (sock, output_token);

    maj_stat = gss_wrap (&min_stat,
			 context_hdl,
			 1,
			 GSS_C_QOP_DEFAULT,
			 input_token,
			 NULL,
			 output_token);
    if (GSS_ERROR(maj_stat))
	gss_err (1, min_stat, "gss_wrap");

    write_token (sock, output_token);

    read_token (sock, input_token);

    maj_stat = gss_unwrap (&min_stat,
			   context_hdl,
			   input_token,
			   output_token,
			   &conf_flag,
			   NULL);
    if(GSS_ERROR(maj_stat))
	gss_err (1, min_stat, "gss_unwrap");

    write_token (sock, output_token);

    gss_release_buffer(&min_stat, output_token);

    return 0;
}
