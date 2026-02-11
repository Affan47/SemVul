z11_enumerate_glyph(gs_font *font, int *pindex,
                         gs_glyph_space_t glyph_space, gs_glyph *pglyph)
{
    gs_font_cid2 *pfont = (gs_font_cid2 *)font;
    int code0 = z11_CIDMap_proc(pfont, GS_MIN_CID_GLYPH);
    int code;

    if(*pindex > pfont->cidata.common.CIDCount)
        return_error(e_rangecheck);

    for (;;) {
        code = z11_CIDMap_proc(pfont, GS_MIN_CID_GLYPH + *pindex);

        if (code < 0) {
            *pindex = 0;
            return 0;
        }
        (*pindex)++;
        if (*pindex == 1 || code != code0)
            break;

    }
    if (glyph_space == GLYPH_SPACE_INDEX)
        *pglyph = GS_MIN_GLYPH_INDEX + (uint)code;
    else
        *pglyph = GS_MIN_CID_GLYPH + (uint)(*pindex - 1);
    return 0;
}
