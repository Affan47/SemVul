worst_cursed_item()
{
    register struct obj *otmp;


    if (near_capacity() >= HVY_ENCUMBER) {
	for (otmp = invent; otmp; otmp = otmp->nobj)
	    if (Cursed_obj(otmp, LOADSTONE)) return otmp;
    }


    if (welded(uwep) && (uright || bimanual(uwep))) {
	otmp = uwep;

    } else if (uarmg && uarmg->cursed) {
	otmp = uarmg;

    } else if (uarms && uarms->cursed) {
	otmp = uarms;

    } else if (uarmc && uarmc->cursed) {
	otmp = uarmc;
    } else if (uarm && uarm->cursed) {
	otmp = uarm;
    } else if (uarmh && uarmh->cursed) {
	otmp = uarmh;
    } else if (uarmf && uarmf->cursed) {
	otmp = uarmf;
#ifdef TOURIST
    } else if (uarmu && uarmu->cursed) {
	otmp = uarmu;
#endif
    } else if (uamul && uamul->cursed) {
	otmp = uamul;
    } else if (uleft && uleft->cursed) {
	otmp = uleft;
    } else if (uright && uright->cursed) {
	otmp = uright;
    } else if (ublindf && ublindf->cursed) {
	otmp = ublindf;

    } else if (welded(uwep)) {
	otmp = uwep;

    } else if (uswapwep && uswapwep->cursed && u.twoweap) {
	otmp = uswapwep;

    } else {
	for (otmp = invent; otmp; otmp = otmp->nobj) {
	    if (!otmp->cursed) continue;
	    if (otmp->otyp == LOADSTONE || confers_luck(otmp))
		break;
	}
    }
    return otmp;
}
