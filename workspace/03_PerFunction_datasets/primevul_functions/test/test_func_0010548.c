suggest_try_special(suginfo_T *su)
{
    char_u	*p;
    size_t	len;
    int		c;
    char_u	word[MAXWLEN];


    p = skiptowhite(su->su_fbadword);
    len = p - su->su_fbadword;
    p = skipwhite(p);
    if (STRLEN(p) == len && STRNCMP(su->su_fbadword, p, len) == 0)
    {


	c = su->su_fbadword[len];
	su->su_fbadword[len] = NUL;
	make_case_word(su->su_fbadword, word, su->su_badflags);
	su->su_fbadword[len] = c;


	add_suggestion(su, &su->su_ga, word, su->su_badlen,
		       RESCORE(SCORE_REP, 0), 0, TRUE, su->su_sallang, FALSE);
    }
}
