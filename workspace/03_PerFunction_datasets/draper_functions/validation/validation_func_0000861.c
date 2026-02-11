check_file_signature(
    const char* md5_buf, R_RSA_PUBLIC_KEY& key,
    DATA_BLOCK& signature, bool& answer
) {
    char clear_buf[MD5_LEN];
    int n, retval;
    DATA_BLOCK clear_signature;
    clear_buf[0]=0;

    n = (int)strlen(md5_buf);
    clear_signature.data = (unsigned char*)clear_buf;
    clear_signature.len = MD5_LEN;
    retval = decrypt_public(key, signature, clear_signature);
    if (retval) {
        fprintf(stderr,
            "check_file_signature: decrypt_public error %d\n", retval
        );
        return retval;
    }
    answer = !strncmp(md5_buf, clear_buf, n);
    return 0;
}
