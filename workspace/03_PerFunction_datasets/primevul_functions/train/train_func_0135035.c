nm_utils_generate_duid_uuid(const NMUuid *uuid)
{
    const guint16 duid_type = htons(4);
    guint8 *      duid_buffer;

    nm_assert(uuid);


    G_STATIC_ASSERT_EXPR(sizeof(duid_type) == 2);
    G_STATIC_ASSERT_EXPR(sizeof(*uuid) == 16);
    duid_buffer = g_malloc(18);
    memcpy(&duid_buffer[0], &duid_type, 2);
    memcpy(&duid_buffer[2], uuid, 16);
    return g_bytes_new_take(duid_buffer, 18);
}
