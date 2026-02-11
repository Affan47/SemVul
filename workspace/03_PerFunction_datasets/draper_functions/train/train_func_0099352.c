tele_restrict(mon)
struct monst *mon;
{
	if (level.flags.noteleport) {
		if (canseemon(mon))
		    pline("A mysterious force prevents %s from teleporting!",
			mon_nam(mon));
		return TRUE;
	}
	return FALSE;
}
