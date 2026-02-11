object_notice_slay(object_type *o_ptr, int flag)
{
	const slay_t *s_ptr;
	bool learned = object_notice_flag(o_ptr, flag);


	if (EASY_LEARN && learned)
	{
		object_notice_ego(o_ptr);

		for (s_ptr = slay_table; s_ptr->slay_flag; s_ptr++)
		{
			if (s_ptr->slay_flag == flag)
			{
				char o_name[40];
				object_desc(o_name, sizeof(o_name), o_ptr, ODESC_BASE);
				msg_format("Your %s %s!", o_name, s_ptr->active_verb);
			}
		}
	}

	object_check_for_ident(o_ptr);
}
