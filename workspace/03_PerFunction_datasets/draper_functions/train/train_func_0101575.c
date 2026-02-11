snd_make_stkrev(int rev_type, sound_type s1, time_type trev, double mix, rate_type sr)
{
    register stkrev_susp_type susp;

    time_type t0 = s1->t0;
    int interp_desc = 0;
    sample_type scale_factor = 1.0F;
    time_type t0_min = t0;
    falloc_generic(susp, stkrev_susp_node, "snd_make_stkrev");
    susp->myrv = initStkEffect(rev_type, trev, round(sr));
stkEffectSetMix(susp->myrv, mix);


    interp_desc = (interp_desc << 2) + interp_style(s1, sr);
    switch (interp_desc) {
      case INTERP_n: susp->susp.fetch = stkrev_n_fetch; break;
      case INTERP_s: susp->susp.fetch = stkrev_s_fetch; break;
      default: snd_badsr(); break;
    }

    susp->terminate_cnt = UNKNOWN;

    if (t0 < s1->t0) sound_prepend_zeros(s1, t0);

    t0_min = min(s1->t0, t0);

    susp->susp.toss_cnt = (long) ((t0 - t0_min) * sr + 0.5);
    if (susp->susp.toss_cnt > 0) {
	susp->susp.keep_fetch = susp->susp.fetch;
	susp->susp.fetch = stkrev_toss_fetch;
    }


    susp->susp.free = stkrev_free;
    susp->susp.sr = sr;
    susp->susp.t0 = t0;
    susp->susp.mark = stkrev_mark;
    susp->susp.print_tree = stkrev_print_tree;
    susp->susp.name = "stkrev";
    susp->logically_stopped = false;
    susp->susp.log_stop_cnt = logical_stop_cnt_cvt(s1);
    susp->susp.current = 0;
    susp->s1 = s1;
    susp->s1_cnt = 0;
    return sound_create((snd_susp_type)susp, t0, sr, scale_factor);
}
