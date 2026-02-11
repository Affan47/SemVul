gwy_serialize_pack_object_header(GByteArray *buffer,
                                 const guchar *object_name)
{
    gint32 value = 0;

    if (!buffer)
        buffer = g_byte_array_new();
    g_byte_array_append(buffer, object_name, strlen(object_name) + 1);
    g_byte_array_append(buffer, (guint8*)&value, sizeof(gint32));

    return buffer;
}
