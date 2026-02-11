update_sound (double freq, int longframe, int linetoggle) {
    static int lastfreq;
    double lines = 0;
    double hpos;

    if (freq < 0)
        freq = lastfreq;
    lastfreq = freq;

    if (!have_sound)
        return;

    if (linetoggle) {
        hpos = maxhpos_short + 0.5;
        lines += 0.5;
    } else {
        if (longframe < 0)
            lines += 0.5;
        else if (longframe > 0)
            lines += 1.0;
        hpos = maxhpos_short;
    }
    lines += maxvpos_nom;

    scaled_sample_evtime = hpos * lines * freq * CYCLE_UNIT / (double) obtainedfreq;
#ifdef SAMPLER
    sampler_evtime = hpos * lines * freq * CYCLE_UNIT;
#endif
}
