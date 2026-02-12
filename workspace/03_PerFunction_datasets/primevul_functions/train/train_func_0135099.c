nm_utils_create_dhcp_iaid(gboolean      legacy_unstable_byteorder,
                          const guint8 *interface_id,
                          gsize         interface_id_len)
{
    guint64 u64;
    guint32 u32;

    u64 = c_siphash_hash(HASH_KEY, interface_id, interface_id_len);
    u32 = (u64 & 0xffffffffu) ^ (u64 >> 32);
    if (legacy_unstable_byteorder) {


        return htole32(u32);
    } else {

        return u32;
    }
}
