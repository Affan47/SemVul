nm_utils_stable_id_parse(const char *stable_id,
                         const char *deviceid,
                         const char *hwaddr,
                         const char *bootid,
                         const char *uuid,
                         char **     out_generated)
{
    gsize    i, idx_start;
    GString *str = NULL;

    g_return_val_if_fail(out_generated, NM_UTILS_STABLE_TYPE_RANDOM);

    if (!stable_id) {
        *out_generated = NULL;
        return NM_UTILS_STABLE_TYPE_UUID;
    }


    idx_start = 0;
    for (i = 0; stable_id[i];) {
        if (stable_id[i] != '$') {
            i++;
            continue;
        }

#define CHECK_PREFIX(prefix)                                                  \
    ({                                                                        \
        gboolean _match = FALSE;                                              \
                                                                              \
        if (g_str_has_prefix(&stable_id[i], "" prefix "")) {                  \
            _match = TRUE;                                                    \
            if (!str)                                                         \
                str = g_string_sized_new(256);                                \
            i += NM_STRLEN(prefix);                                           \
            g_string_append_len(str, &(stable_id)[idx_start], i - idx_start); \
            idx_start = i;                                                    \
        }                                                                     \
        _match;                                                               \
    })
        if (CHECK_PREFIX("${CONNECTION}"))
            _stable_id_append(str, uuid);
        else if (CHECK_PREFIX("${BOOT}"))
            _stable_id_append(str, bootid);
        else if (CHECK_PREFIX("${DEVICE}"))
            _stable_id_append(str, deviceid);
        else if (CHECK_PREFIX("${MAC}"))
            _stable_id_append(str, hwaddr);
        else if (g_str_has_prefix(&stable_id[i], "${RANDOM}")) {


            if (str)
                g_string_free(str, TRUE);
            *out_generated = NULL;
            return NM_UTILS_STABLE_TYPE_RANDOM;
        } else {


            i++;


            if (stable_id[i] == '$')
                i++;
        }
    }
#undef CHECK_PREFIX

    if (!str) {
        *out_generated = NULL;
        return NM_UTILS_STABLE_TYPE_STABLE_ID;
    }

    if (idx_start < i)
        g_string_append_len(str, &stable_id[idx_start], i - idx_start);
    *out_generated = g_string_free(str, FALSE);
    return NM_UTILS_STABLE_TYPE_GENERATED;
}
