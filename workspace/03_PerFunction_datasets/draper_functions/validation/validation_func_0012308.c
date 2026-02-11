obj_resists(obj, ochance, achance)
struct obj *obj;
int ochance, achance;
{
	if (obj->otyp == AMULET_OF_YENDOR ||
	    obj->otyp == SPE_BOOK_OF_THE_DESU ||
	    obj->otyp == CANDELABRUM_OF_INVOCATION ||
	    obj->otyp == BELL_OF_OPENING ||
	    obj->otyp == CLAPPER_OF_OPENING ||
	    (obj->otyp == CORPSE && is_rider(&mons[obj->corpsenm]))) {
		return TRUE;
	} else {
		int chance = rn2(100);

		return((boolean)(chance < (obj->oartifact ? achance : ochance)));
	}
}
