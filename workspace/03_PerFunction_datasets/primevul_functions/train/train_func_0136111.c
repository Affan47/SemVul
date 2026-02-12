static int process_style(ASS_Track *track, char *str)
{

    char *token;
    char *tname;
    char *p = str;
    char *format;
    char *q;
    int sid;
    ASS_Style *style;
    ASS_Style *target;

    if (!track->style_format) {


        if (track->track_type == TRACK_TYPE_SSA)
            track->style_format = strdup(ssa_style_format);
        else
            track->style_format = strdup(ass_style_format);
        if (!track->style_format)
            return -1;
    }

    q = format = strdup(track->style_format);
    if (!q)
        return -1;

    ass_msg(track->library, MSGL_V, "[%p] Style: %s", track, str);

    sid = ass_alloc_style(track);
    if (sid < 0) {
        free(format);
        return -1;
    }

    style = track->styles + sid;
    target = style;


    style->ScaleX = 100.;
    style->ScaleY = 100.;

    while (1) {
        NEXT(q, tname);
        NEXT(p, token);

        PARSE_START
            STARREDSTRVAL(Name)
            STRVAL(FontName)
            COLORVAL(PrimaryColour)
            COLORVAL(SecondaryColour)
            COLORVAL(OutlineColour)
            COLORVAL(BackColour)


            if (track->track_type == TRACK_TYPE_SSA)
                target->OutlineColour = target->BackColour;
            FPVAL(FontSize)
            INTVAL(Bold)
            INTVAL(Italic)
            INTVAL(Underline)
            INTVAL(StrikeOut)
            FPVAL(Spacing)
            FPVAL(Angle)
            INTVAL(BorderStyle)
            INTVAL(Alignment)
            if (track->track_type == TRACK_TYPE_ASS)
                target->Alignment = numpad2align(target->Alignment);

            else if (target->Alignment == 8)
                target->Alignment = 3;
            else if (target->Alignment == 4)
                target->Alignment = 11;
            INTVAL(MarginL)
            INTVAL(MarginR)
            INTVAL(MarginV)
            INTVAL(Encoding)
            FPVAL(ScaleX)
            FPVAL(ScaleY)
            FPVAL(Outline)
            FPVAL(Shadow)
        PARSE_END
    }
    free(format);
    style->ScaleX = FFMAX(style->ScaleX, 0.) / 100.;
    style->ScaleY = FFMAX(style->ScaleY, 0.) / 100.;
    style->Spacing = FFMAX(style->Spacing, 0.);
    style->Outline = FFMAX(style->Outline, 0.);
    style->Shadow = FFMAX(style->Shadow, 0.);
    style->Bold = !!style->Bold;
    style->Italic = !!style->Italic;
    style->Underline = !!style->Underline;
    style->StrikeOut = !!style->StrikeOut;
    if (!style->Name)
        style->Name = strdup("Default");
    if (!style->FontName)
        style->FontName = strdup("Arial");
    if (!style->Name || !style->FontName) {
        ass_free_style(track, sid);
        track->n_styles--;
        return -1;
    }
    if (strcmp(target->Name, "Default") == 0)
        track->default_style = sid;
    return 0;

}
