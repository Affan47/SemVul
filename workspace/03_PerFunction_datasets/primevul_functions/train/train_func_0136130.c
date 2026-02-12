static bool detect_legacy_conv_subs(ASS_Track *track)
{


    if (track->parser_priv->header_flags
            ^ (SINFO_PLAYRESX | SINFO_PLAYRESY | GENBY_FFMPEG))
        return false;


    if (track->n_styles != 2
        || strncmp(track->styles[1].Name, "Default", 7))
        return false;

    return true;
}
