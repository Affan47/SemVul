lesshungry(num)
register int num;
{

	boolean iseating = (occupation == eatfood) || force_save_hs;
#ifdef DEBUG
	debugpline("lesshungry(%d)", num);
#endif
	u.uhunger += num;
	if(u.uhunger >= 2000) {
	    if (!iseating || victual.canchoke) {
		if (iseating) {
		    choke(victual.piece);
		    reset_eat();
		} else
		    choke(occupation == opentin ? tin.tin : (struct obj *)0);

	    }
	} else {


	    if (u.uhunger >= 1500) {
		if (!victual.eating || (victual.eating && !victual.fullwarn)) {
		    pline("You're having a hard time getting all of it down.");
		    nomovemsg = "You're finally finished.";
		    if (!victual.eating)
			multi = -2;
		    else {
			victual.fullwarn = TRUE;
			if (victual.canchoke && victual.reqtime > 1) {

			    if (yn_function("Stop eating?",ynchars,'y')=='y') {
				reset_eat();
				nomovemsg = (char *)0;
			    }
			}
		    }
		}
	    }
	}
	newuhs(FALSE);
}
