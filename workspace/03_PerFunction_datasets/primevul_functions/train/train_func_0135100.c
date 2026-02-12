_host_id_read(guint8 **out_host_id, gsize *out_host_id_len)
{
#define SECRET_KEY_LEN 32u
    guint8                               sha256_digest[NM_UTILS_CHECKSUM_LENGTH_SHA256];
    nm_auto_clear_secret_ptr NMSecretPtr file_content = {0};
    const guint8 *                       secret_arr;
    gsize                                secret_len;
    GError *                             error = NULL;
    gboolean                             success;

    if (!nm_utils_file_get_contents(-1,
                                    SECRET_KEY_FILE,
                                    10 * 1024,
                                    NM_UTILS_FILE_GET_CONTENTS_FLAG_SECRET,
                                    &file_content.str,
                                    &file_content.len,
                                    NULL,
                                    &error)) {
        if (!nm_utils_error_is_notfound(error)) {
            nm_log_warn(LOGD_CORE,
                        "secret-key: failure reading secret key in \"%s\": %s (generate new key)",
                        SECRET_KEY_FILE,
                        error->message);
        }
        g_clear_error(&error);
    } else if (file_content.len >= NM_STRLEN(SECRET_KEY_V2_PREFIX) + SECRET_KEY_LEN
               && memcmp(file_content.bin, SECRET_KEY_V2_PREFIX, NM_STRLEN(SECRET_KEY_V2_PREFIX))
                      == 0) {


        secret_arr = _host_id_hash_v2(file_content.bin, file_content.len, sha256_digest);
        secret_len = NM_UTILS_CHECKSUM_LENGTH_SHA256;
        success    = TRUE;
        nm_log_dbg(LOGD_CORE,
                   "secret-key: v2 secret key loaded from \"%s\" (%zu bytes)",
                   SECRET_KEY_FILE,
                   file_content.len);
        goto out;
    } else if (file_content.len >= 16) {
        secret_arr = file_content.bin;
        secret_len = file_content.len;
        success    = TRUE;
        nm_log_dbg(LOGD_CORE,
                   "secret-key: v1 secret key loaded from \"%s\" (%zu bytes)",
                   SECRET_KEY_FILE,
                   file_content.len);
        goto out;
    } else {


        nm_log_warn(LOGD_CORE,
                    "secret-key: too short secret key in \"%s\" (generate new key)",
                    SECRET_KEY_FILE);
    }


    {
#define SECRET_KEY_LEN_BASE64 ((((SECRET_KEY_LEN / 3) + 1) * 4) + 4)
        guint8 rnd_buf[SECRET_KEY_LEN];
        guint8 new_content[NM_STRLEN(SECRET_KEY_V2_PREFIX) + SECRET_KEY_LEN_BASE64];
        int    base64_state = 0;
        int    base64_save  = 0;
        gsize  len;

        success = nm_utils_random_bytes(rnd_buf, sizeof(rnd_buf));


        memcpy(new_content, SECRET_KEY_V2_PREFIX, NM_STRLEN(SECRET_KEY_V2_PREFIX));
        len = NM_STRLEN(SECRET_KEY_V2_PREFIX);
        len += g_base64_encode_step(rnd_buf,
                                    sizeof(rnd_buf),
                                    FALSE,
                                    (char *) &new_content[len],
                                    &base64_state,
                                    &base64_save);
        len +=
            g_base64_encode_close(FALSE, (char *) &new_content[len], &base64_state, &base64_save);
        nm_assert(len <= sizeof(new_content));

        secret_arr = _host_id_hash_v2(new_content, len, sha256_digest);
        secret_len = NM_UTILS_CHECKSUM_LENGTH_SHA256;

        if (!success)
            nm_log_warn(LOGD_CORE,
                        "secret-key: failure to generate good random data for secret-key (use "
                        "non-persistent key)");
        else if (nm_utils_get_testing()) {

        } else if (!nm_utils_file_set_contents(SECRET_KEY_FILE,
                                               (const char *) new_content,
                                               len,
                                               0600,
                                               NULL,
                                               &error)) {
            nm_log_warn(
                LOGD_CORE,
                "secret-key: failure to persist secret key in \"%s\" (%s) (use non-persistent key)",
                SECRET_KEY_FILE,
                error->message);
            g_clear_error(&error);
            success = FALSE;
        } else
            nm_log_dbg(LOGD_CORE,
                       "secret-key: persist new v2 secret key to \"%s\" (%zu bytes)",
                       SECRET_KEY_FILE,
                       len);

        nm_explicit_bzero(rnd_buf, sizeof(rnd_buf));
        nm_explicit_bzero(new_content, sizeof(new_content));
    }

out:
    *out_host_id_len = secret_len;
    *out_host_id     = nm_memdup(secret_arr, secret_len);
    return success;
}
