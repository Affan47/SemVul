set_search_by_age(INTVL_S *age, SEARCHPGM *pgm, int age_uses_sentdate)
{
    time_t         now, comparetime;
    struct tm     *tm;
    unsigned short i;

    if(!(age && pgm))
      return;

    now = time(0);

    if(age->imin >= 0L && age->imin == age->imax){
	comparetime = now;
	comparetime -= (age->imin * 86400L);
	tm = localtime(&comparetime);
	if(tm && tm->tm_year >= 70){
	    i = mail_shortdate(tm->tm_year - 70, tm->tm_mon + 1,
			       tm->tm_mday);
	    if(age_uses_sentdate)
	      pgm->senton = i;
	    else
	      pgm->on = i;
	}
    }
    else{


	if(age->imin > 0L && age->imin < 20000L){
	    comparetime = now;
	    comparetime -= ((age->imin - 1L) * 86400L);
	    tm = localtime(&comparetime);
	    if(tm && tm->tm_year >= 70){
		i = mail_shortdate(tm->tm_year - 70, tm->tm_mon + 1,
				   tm->tm_mday);
		if(age_uses_sentdate)
		  pgm->sentbefore = i;
		else
		  pgm->before = i;
	    }
	}

	if(age->imax >= 0L && age->imax < 20000L){
	    comparetime = now;
	    comparetime -= (age->imax * 86400L);
	    tm = localtime(&comparetime);
	    if(tm && tm->tm_year >= 70){
		i = mail_shortdate(tm->tm_year - 70, tm->tm_mon + 1,
				   tm->tm_mday);
		if(age_uses_sentdate)
		  pgm->sentsince = i;
		else
		  pgm->since = i;
	    }
	}
    }
}
