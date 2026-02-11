read_data (PacketReader *reader, XDMCPData *data)
{
    guint16 i;

    data->length = read_card16 (reader);
    data->data = g_malloc (sizeof (guint8) * data->length);
    for (i = 0; i < data->length; i++)
        data->data[i] = read_card8 (reader);
}
