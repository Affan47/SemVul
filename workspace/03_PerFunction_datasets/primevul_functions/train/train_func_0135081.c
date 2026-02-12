_host_id_read_timestamp(gboolean      use_secret_key_file,
                        const guint8 *host_id,
                        gsize         host_id_len,
                        gint64 *      out_timestamp_ns)
{
    struct stat st;
    gint64      now;
    guint64     v;

    if (use_secret_key_file && stat(SECRET_KEY_FILE, &st) == 0) {


        *out_timestamp_ns = nm_utils_timespec_to_nsec(&st.st_mtim);
        return TRUE;
    }


#define EPOCH_TWO_YEARS (G_GINT64_CONSTANT(2 * 365 * 24 * 3600) * NM_UTILS_NSEC_PER_SEC)

    v = nm_hash_siphash42(1156657133u, host_id, host_id_len);

    now = time(NULL);
    *out_timestamp_ns =
        NM_MAX((gint64) 1,
               (now * NM_UTILS_NSEC_PER_SEC) - ((gint64)(v % ((guint64)(EPOCH_TWO_YEARS)))));
    return FALSE;
}
