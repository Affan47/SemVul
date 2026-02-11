obj_desc_get_basename(const object_type *o_ptr, bool aware)
{
	bool show_flavor = o_ptr->kind->flavor ? TRUE : FALSE;


	if (o_ptr->ident & IDENT_STORE) show_flavor = FALSE;
	if (aware && !OPT(show_flavors)) show_flavor = FALSE;


	if (o_ptr->artifact && aware)
		return o_ptr->kind->name;


	switch (o_ptr->tval)
	{
		case TV_SKELETON:
		case TV_BOTTLE:
		case TV_JUNK:
		case TV_SPIKE:
		case TV_FLASK:
		case TV_CHEST:
		case TV_SHOT:
		case TV_BOLT:
		case TV_ARROW:
		case TV_BOW:
		case TV_HAFTED:
		case TV_POLEARM:
		case TV_SWORD:
		case TV_DIGGING:
		case TV_BOOTS:
		case TV_GLOVES:
		case TV_CLOAK:
		case TV_CROWN:
		case TV_HELM:
		case TV_SHIELD:
		case TV_SOFT_ARMOR:
		case TV_HARD_ARMOR:
		case TV_DRAG_ARMOR:
		case TV_LIGHT:
			return o_ptr->kind->name;

		case TV_AMULET:
			return (show_flavor ? "& # Amulet~" : "& Amulet~");

		case TV_RING:
			return (show_flavor ? "& # Ring~" : "& Ring~");

		case TV_STAFF:
			return (show_flavor ? "& # Sta|ff|ves|" : "& Sta|ff|ves|");

		case TV_WAND:
			return (show_flavor ? "& # Wand~" : "& Wand~");

		case TV_ROD:
			return (show_flavor ? "& # Rod~" : "& Rod~");

		case TV_POTION:
			return (show_flavor ? "& # Potion~" : "& Potion~");

		case TV_SCROLL:
			return (show_flavor ? "& Scroll~ titled #" : "& Scroll~");

		case TV_MAGIC_BOOK:
			return "& Book~ of Magic Spells #";

		case TV_PRAYER_BOOK:
			return "& Holy Book~ of Prayers #";

		case TV_FOOD:
			if (o_ptr->sval > SV_FOOD_MIN_SHROOM)
				return (show_flavor ? "& # Mushroom~" : "& Mushroom~");
			else
				return o_ptr->kind->name;
	}

	return "(nothing)";
}
