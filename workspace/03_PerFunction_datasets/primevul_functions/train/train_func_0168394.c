chacha20_poly1305_set_key(struct ssh_cipher_struct *cipher,
                          void *key,
                          UNUSED_PARAM(void *IV))
{
    struct chacha20_poly1305_keysched *ctx = NULL;
    uint8_t *u8key = key;
    int ret = SSH_ERROR, rv;

    if (cipher->chacha20_schedule == NULL) {
        ctx = calloc(1, sizeof(*ctx));
        if (ctx == NULL) {
            return -1;
        }
        cipher->chacha20_schedule = ctx;
    } else {
        ctx = cipher->chacha20_schedule;
    }


    ctx->main_evp = EVP_CIPHER_CTX_new();
    if (ctx->main_evp == NULL) {
        SSH_LOG(SSH_LOG_WARNING, "EVP_CIPHER_CTX_new failed");
        goto out;
    }
    rv = EVP_EncryptInit_ex(ctx->main_evp, EVP_chacha20(), NULL, u8key, NULL);
    if (rv != 1) {
        SSH_LOG(SSH_LOG_WARNING, "EVP_CipherInit failed");
        goto out;
    }

    ctx->header_evp = EVP_CIPHER_CTX_new();
    if (ctx->header_evp == NULL) {
        SSH_LOG(SSH_LOG_WARNING, "EVP_CIPHER_CTX_new failed");
        goto out;
    }
    ret = EVP_EncryptInit_ex(ctx->header_evp, EVP_chacha20(), NULL,
                             u8key + CHACHA20_KEYLEN, NULL);
    if (ret != 1) {
        SSH_LOG(SSH_LOG_WARNING, "EVP_CipherInit failed");
        goto out;
    }


    ctx->mctx = EVP_MD_CTX_new();
    if (ctx->mctx == NULL) {
        SSH_LOG(SSH_LOG_WARNING, "EVP_MD_CTX_new failed");
        return SSH_ERROR;
    }

    ret = SSH_OK;
out:
    if (ret != SSH_OK) {
        chacha20_poly1305_cleanup(cipher);
    }
    return ret;
}
