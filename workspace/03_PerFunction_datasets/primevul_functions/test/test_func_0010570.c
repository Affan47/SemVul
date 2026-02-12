spell_suggest_intern(suginfo_T *su, int interactive)
{

    suggest_load_files();


    suggest_try_special(su);


    suggest_try_change(su);


    if (sps_flags & SPS_DOUBLE)
	score_comp_sal(su);


    if ((sps_flags & SPS_FAST) == 0)
    {
	if (sps_flags & SPS_BEST)


	    rescore_suggestions(su);


	suggest_try_soundalike_prep();
	su->su_maxscore = SCORE_SFMAX1;
	su->su_sfmaxscore = SCORE_MAXINIT * 3;
	suggest_try_soundalike(su);
	if (su->su_ga.ga_len < SUG_CLEAN_COUNT(su))
	{


	    su->su_maxscore = SCORE_SFMAX2;
	    suggest_try_soundalike(su);
	    if (su->su_ga.ga_len < SUG_CLEAN_COUNT(su))
	    {


		su->su_maxscore = SCORE_SFMAX3;
		suggest_try_soundalike(su);
	    }
	}
	su->su_maxscore = su->su_sfmaxscore;
	suggest_try_soundalike_finish();
    }


    ui_breakcheck();
    if (interactive && got_int)
    {
	(void)vgetc();
	got_int = FALSE;
    }

    if ((sps_flags & SPS_DOUBLE) == 0 && su->su_ga.ga_len != 0)
    {
	if (sps_flags & SPS_BEST)

	    rescore_suggestions(su);


	check_suggestions(su, &su->su_ga);
	(void)cleanup_suggestions(&su->su_ga, su->su_maxscore, su->su_maxcount);
    }
}
