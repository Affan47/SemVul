aes_ctr_encrypt(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
    ErlNifBinary key, ivec, text;
    AES_KEY aes_key;
    unsigned char ivec_clone[16];
    unsigned char ecount_buf[AES_BLOCK_SIZE];
    unsigned int num = 0;
    ERL_NIF_TERM ret;

    if (!enif_inspect_iolist_as_binary(env, argv[0], &key)
	|| AES_set_encrypt_key(key.data, key.size*8, &aes_key) != 0
	|| !enif_inspect_binary(env, argv[1], &ivec) || ivec.size != 16
	|| !enif_inspect_iolist_as_binary(env, argv[2], &text)) {
	return enif_make_badarg(env);
    }
    memcpy(ivec_clone, ivec.data, 16);
    memset(ecount_buf, 0, sizeof(ecount_buf));
    AES_ctr128_encrypt((unsigned char *) text.data,
		       enif_make_new_binary(env, text.size, &ret),
		       text.size, &aes_key, ivec_clone, ecount_buf, &num);
    CONSUME_REDS(env,text);


    return ret;
}
