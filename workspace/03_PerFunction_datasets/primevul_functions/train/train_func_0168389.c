chacha20_poly1305_packet_setup(struct ssh_cipher_struct *cipher,
                               uint64_t seq,
                               int do_encrypt)
{
    struct chacha20_poly1305_keysched *ctx = cipher->chacha20_schedule;
    uint8_t poly_key[CHACHA20_BLOCKSIZE];
    int ret = SSH_ERROR, len, rv;


    if (do_encrypt) {
        rv = chacha20_poly1305_set_iv(cipher, seq, do_encrypt);
        if (rv != SSH_OK) {
            return SSH_ERROR;
        }
    }


    rv = EVP_CipherUpdate(ctx->main_evp, poly_key, &len,
                           (unsigned char *)zero_block, sizeof(zero_block));
    if (rv != 1 || len != CHACHA20_BLOCKSIZE) {
        SSH_LOG(SSH_LOG_WARNING, "EVP_EncryptUpdate failed");
        goto out;
    }
#ifdef DEBUG_CRYPTO
    ssh_log_hexdump("poly_key", poly_key, POLY1305_KEYLEN);
#endif


    if (ctx->key == NULL) {

        ctx->key = EVP_PKEY_new_mac_key(EVP_PKEY_POLY1305, NULL,
                                        poly_key, POLY1305_KEYLEN);
        if (ctx->key == NULL) {
            SSH_LOG(SSH_LOG_WARNING, "EVP_PKEY_new_mac_key failed");
            goto out;
        }
        rv = EVP_DigestSignInit(ctx->mctx, &ctx->pctx, NULL, NULL, ctx->key);
        if (rv != 1) {
            SSH_LOG(SSH_LOG_WARNING, "EVP_DigestSignInit failed");
            goto out;
        }
    } else {

        rv = EVP_PKEY_CTX_ctrl(ctx->pctx, -1, EVP_PKEY_OP_SIGNCTX,
                                EVP_PKEY_CTRL_SET_MAC_KEY,
                                POLY1305_KEYLEN, (void *)poly_key);
        if (rv <= 0) {
            SSH_LOG(SSH_LOG_WARNING, "EVP_PKEY_CTX_ctrl failed");
            goto out;
        }
    }

    ret = SSH_OK;
out:
    explicit_bzero(poly_key, sizeof(poly_key));
    return ret;
}
