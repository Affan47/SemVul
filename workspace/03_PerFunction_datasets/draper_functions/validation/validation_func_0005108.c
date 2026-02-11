HPDF_Type1Font_New  (HPDF_MMgr        mmgr,
                     HPDF_FontDef     fontdef,
                     HPDF_Encoder     encoder,
                     HPDF_Xref        xref)
{
    HPDF_Dict font;
    HPDF_FontAttr attr;
    HPDF_Type1FontDefAttr fontdef_attr;
    HPDF_BasicEncoderAttr encoder_attr;
    HPDF_STATUS ret = 0;
    HPDF_UINT i;

    HPDF_PTRACE ((" HPDF_Type1Font_New\n"));


    if (encoder->type != HPDF_ENCODER_TYPE_SINGLE_BYTE) {
        HPDF_SetError(mmgr->error, HPDF_INVALID_ENCODER_TYPE, 0);
        return NULL;
    }

    if (fontdef->type != HPDF_FONTDEF_TYPE_TYPE1) {
        HPDF_SetError(mmgr->error, HPDF_INVALID_FONTDEF_TYPE, 0);
        return NULL;
    }

    font = HPDF_Dict_New (mmgr);
    if (!font)
        return NULL;

    font->header.obj_class |= HPDF_OSUBCLASS_FONT;

    attr = HPDF_GetMem (mmgr, sizeof(HPDF_FontAttr_Rec));
    if (!attr) {
        HPDF_Dict_Free (font);
        return NULL;
    }

    font->header.obj_class |= HPDF_OSUBCLASS_FONT;
    font->write_fn = Type1Font_OnWrite;
    font->free_fn = Type1Font_OnFree;

    HPDF_MemSet (attr, 0, sizeof(HPDF_FontAttr_Rec));

    font->attr = attr;
    attr->type = HPDF_FONT_TYPE1;
    attr->writing_mode = HPDF_WMODE_HORIZONTAL;
    attr->text_width_fn = Type1Font_TextWidth;
    attr->measure_text_fn = Type1Font_MeasureText;
    attr->fontdef = fontdef;
    attr->encoder = encoder;
    attr->xref = xref;


    attr->widths = HPDF_GetMem (mmgr, sizeof(HPDF_INT16) * 256);
    if (!attr->widths) {
        HPDF_Dict_Free (font);
        return NULL;
    }

    encoder_attr = (HPDF_BasicEncoderAttr)encoder->attr;

    HPDF_MemSet (attr->widths, 0, sizeof(HPDF_INT16) * 256);
    for (i = encoder_attr->first_char; i <= encoder_attr->last_char; i++) {
        HPDF_UNICODE u = encoder_attr->unicode_map[i];

        HPDF_UINT16 w = HPDF_Type1FontDef_GetWidth (fontdef, u);
        attr->widths[i] = w;
    }

    fontdef_attr = (HPDF_Type1FontDefAttr)fontdef->attr;

    ret += HPDF_Dict_AddName (font, "Type", "Font");
    ret += HPDF_Dict_AddName (font, "BaseFont", fontdef->base_font);
    ret += HPDF_Dict_AddName (font, "Subtype", "Type1");

    if (!fontdef_attr->is_base14font) {
        if (fontdef->missing_width != 0)
            ret += HPDF_Dict_AddNumber (font, "MissingWidth",
                    fontdef->missing_width);

        ret += Type1Font_CreateDescriptor (mmgr, font, xref);
    }

    if (ret != HPDF_OK) {
        HPDF_Dict_Free (font);
        return NULL;
    }

    if (HPDF_Xref_Add (xref, font) != HPDF_OK)
        return NULL;

    return font;
}
