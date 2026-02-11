confused_book(spellbook)
struct obj *spellbook;
{
	boolean gone = FALSE;

	if (!rn2(3) && spellbook->otyp != SPE_BOOK_OF_THE_DEAD) {
	    spellbook->in_use = TRUE;
	    pline(
	"Being confused you have difficulties in controlling your actions.");
	    display_nhwindow(WIN_MESSAGE, FALSE);
	    You("accidentally tear the spellbook to pieces.");
	    if (!objects[spellbook->otyp].oc_name_known &&
		!objects[spellbook->otyp].oc_uname)
		docall(spellbook);
	    useup(spellbook);
	    gone = TRUE;
	} else {
	    You("find yourself reading the %s line over and over again.",
		spellbook == book ? "next" : "first");
	}
	return gone;
}
