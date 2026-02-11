wield_slot(const object_type *o_ptr)
{

	switch (o_ptr->tval)
	{
		case TV_DIGGING:
		case TV_HAFTED:
		case TV_POLEARM:
		case TV_SWORD: return (INVEN_WIELD);

		case TV_BOW: return (INVEN_BOW);

		case TV_RING:
			return p_ptr->inventory[INVEN_RIGHT].kind ? INVEN_LEFT : INVEN_RIGHT;

		case TV_AMULET: return (INVEN_NECK);

		case TV_LIGHT: return (INVEN_LIGHT);

		case TV_DRAG_ARMOR:
		case TV_HARD_ARMOR:
		case TV_SOFT_ARMOR: return (INVEN_BODY);

		case TV_CLOAK: return (INVEN_OUTER);

		case TV_SHIELD: return (INVEN_ARM);

		case TV_CROWN:
		case TV_HELM: return (INVEN_HEAD);

		case TV_GLOVES: return (INVEN_HANDS);

		case TV_BOOTS: return (INVEN_FEET);

		case TV_BOLT:
		case TV_ARROW:
		case TV_SHOT: return wield_slot_ammo(o_ptr);
	}


	return (-1);
}
