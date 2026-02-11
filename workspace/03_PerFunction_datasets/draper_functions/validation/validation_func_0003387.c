obj_desc_show_weapon(const object_type *o_ptr)
{
	bitflag f[OF_SIZE];

	object_flags(o_ptr, f);

	if (of_has(f, OF_SHOW_MODS)) return TRUE;
	if (o_ptr->to_h && o_ptr->to_d) return TRUE;


	if ((o_ptr->to_h || o_ptr->to_d) && !object_flavor_is_aware(o_ptr)) return TRUE;

	switch (o_ptr->tval)
	{
		case TV_SHOT:
		case TV_BOLT:
		case TV_ARROW:
		case TV_BOW:
		case TV_HAFTED:
		case TV_POLEARM:
		case TV_SWORD:
		case TV_DIGGING:
		{
			return TRUE;
		}
	}

	return FALSE;
}
