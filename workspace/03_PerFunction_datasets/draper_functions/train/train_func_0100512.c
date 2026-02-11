fourxm_probe(AVProbeData *p)
{
    if ((AV_RL32(&p->buf[0]) != RIFF_TAG) ||
        (AV_RL32(&p->buf[8]) != FOURXMV_TAG))
        return 0;

    return AVPROBE_SCORE_MAX;
}
