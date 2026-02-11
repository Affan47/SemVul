lame_init_internal_flags(lame_internal_flags* gfc)
{
    if (NULL == gfc)
        return -1;

    gfc->cfg.vbr_min_bitrate_index = 1;
    gfc->cfg.vbr_max_bitrate_index = 13;
    gfc->cfg.decode_on_the_fly = 0;
    gfc->cfg.findReplayGain = 0;
    gfc->cfg.findPeakSample = 0;

    gfc->sv_qnt.OldValue[0] = 180;
    gfc->sv_qnt.OldValue[1] = 180;
    gfc->sv_qnt.CurrentStep[0] = 4;
    gfc->sv_qnt.CurrentStep[1] = 4;
    gfc->sv_qnt.masking_lower = 1;


    gfc->sv_enc.mf_samples_to_encode = ENCDELAY + POSTDELAY;
    gfc->sv_enc.mf_size = ENCDELAY - MDCTDELAY;
    gfc->ov_enc.encoder_padding = 0;
    gfc->ov_enc.encoder_delay = ENCDELAY;

    gfc->ov_rpg.RadioGain = 0;
    gfc->ov_rpg.noclipGainChange = 0;
    gfc->ov_rpg.noclipScale = -1.0;

    gfc->ATH = lame_calloc(ATH_t, 1);
    if (NULL == gfc->ATH)
        return -2;

    gfc->sv_rpg.rgdata = lame_calloc(replaygain_t, 1);
    if (NULL == gfc->sv_rpg.rgdata) {
        return -2;
    }
    return 0;
}
