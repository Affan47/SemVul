object_effect(const object_type *o_ptr)
{
	if (o_ptr->name1)
		return a_info[o_ptr->name1].effect;
	else
		return k_info[o_ptr->k_idx].effect;
}
