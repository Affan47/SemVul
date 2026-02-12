evp_cipher_aead_get_length(struct ssh_cipher_struct *cipher,
                           void *in,
                           uint8_t *out,
                           size_t len,
                           uint64_t seq)
{
    (void)cipher;
    (void)seq;


    memcpy(out, in, len);

    return SSH_OK;
}
