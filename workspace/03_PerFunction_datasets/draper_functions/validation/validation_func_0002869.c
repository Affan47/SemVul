input_file_read_extended (GvaInputFile *input_file,
                          GMappedFile *mapped_file)
{
        GvaInpHeaderExtended *header;
        const gchar *contents;
        gsize length;

        contents = g_mapped_file_get_contents (mapped_file);
        length = g_mapped_file_get_length (mapped_file);

        if (length < sizeof (GvaInpHeaderExtended))
                return FALSE;

        if (memcmp (contents, "XINP\0\0\0", 7) != 0)
                return FALSE;

        header = (GvaInpHeaderExtended *) contents;

        input_file->priv->game = g_strndup (header->rom_name, 9);
        input_file->priv->origin = g_strndup (header->origin, 32);
        input_file->priv->timestamp = GINT32_FROM_LE (header->timestamp);

        input_file->priv->format = g_strdup ("INP extended format");

        if (gva_get_debug_flags () & GVA_DEBUG_INP)
                input_file_dump_header (input_file);

        return TRUE;
}
