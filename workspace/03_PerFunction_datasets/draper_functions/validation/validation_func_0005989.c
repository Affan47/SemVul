mono_metadata_generic_param_equal (MonoGenericParam *p1, MonoGenericParam *p2, gboolean signature_only)
{
	if (p1 == p2)
		return TRUE;
	if (mono_generic_param_num (p1) != mono_generic_param_num (p2))
		return FALSE;
	if (p1->serial != p2->serial)
		return FALSE;


	if (mono_generic_param_owner (p1) == mono_generic_param_owner (p2) &&
	    (mono_generic_param_owner (p1) || p1->image == p2->image))
		return TRUE;


	return signature_only;
}
