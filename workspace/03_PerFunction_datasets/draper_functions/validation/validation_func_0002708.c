zchar_charstring_data(gs_font *font, const ref *pgref, gs_glyph_data_t *pgd)
{
    ref *pcstr;

    if (dict_find(&pfont_data(font)->CharStrings, pgref, &pcstr) <= 0)
        return_error(e_undefined);
    if (!r_has_type(pcstr, t_string)) {


        if (font->FontType == ft_encrypted &&
            charstring_is_notdef_proc(font->memory, pcstr)
            )
            return charstring_make_notdef(pgd, font);
        else
            return_error(e_typecheck);
    }
    gs_glyph_data_from_string(pgd, pcstr->value.const_bytes, r_size(pcstr),
                              NULL);
    return 0;
}
