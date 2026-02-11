id3tag_set_fieldvalue_utf16(lame_t gfp, const unsigned short *fieldvalue)
{
    if (fieldvalue && *fieldvalue) {
        size_t dx = hasUcs2ByteOrderMarker(fieldvalue[0]);
        unsigned short const separator = fromLatin1Char(fieldvalue, '=');
        char fid[5] = {0,0,0,0,0};
        uint32_t const frame_id = toID3v2TagId_ucs2(fieldvalue);
        if (local_ucs2_strlen(fieldvalue) < (5+dx) || fieldvalue[4+dx] != separator) {
            return -1;
        }
        fid[0] = (frame_id >> 24) & 0x0ff;
        fid[1] = (frame_id >> 16) & 0x0ff;
        fid[2] = (frame_id >> 8) & 0x0ff;
        fid[3] = frame_id & 0x0ff;
        if (frame_id != 0) {
            unsigned short* txt = 0;
            int     rc;
            local_ucs2_substr(&txt, fieldvalue, dx+5, local_ucs2_strlen(fieldvalue));
            rc = id3tag_set_textinfo_utf16(gfp, fid, txt);
            free(txt);
            return rc;
        }
    }
    return -1;
}
