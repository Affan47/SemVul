use_candelabrum(obj)
register struct obj *obj;
{
	const char *s = (obj->spe != 1) ? "candles" : "candle";

	if(Underwater) {
		You("cannot make fire under water.");
		return;
	}
	if(obj->lamplit) {
		You("snuff the %s.", s);
		end_burn(obj, TRUE);
		return;
	}
	if(obj->spe <= 0) {
		pline("This %s has no %s.", xname(obj), s);
		return;
	}
	if(u.uswallow || obj->cursed) {
		if (!Blind)
		    pline_The("%s %s for a moment, then %s.",
			      s, vtense(s, "flicker"), vtense(s, "die"));
		return;
	}
	if(obj->spe < 7) {
		There("%s only %d %s in %s.",
		      vtense(s, "are"), obj->spe, s, the(xname(obj)));
		if (!Blind)
		    pline("%s lit.  %s dimly.",
			  obj->spe == 1 ? "It is" : "They are",
			  Tobjnam(obj, "shine"));
	} else {
		pline("%s's %s burn%s", The(xname(obj)), s,
			(Blind ? "." : " brightly!"));
	}
	if (!invocation_pos(u.ux, u.uy)) {
		pline_The("%s %s being rapidly consumed!", s, vtense(s, "are"));
		obj->age /= 2;
	} else {
		if(obj->spe == 7) {
		    if (Blind)
		      pline("%s a strange warmth!", Tobjnam(obj, "radiate"));
		    else
		      pline("%s with a strange light!", Tobjnam(obj, "glow"));
		}
		obj->known = 1;
	}
	begin_burn(obj, FALSE);
}
