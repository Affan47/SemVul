static bool match_keycode(struct hid_usage *usage,
			  unsigned int cur_idx, unsigned int keycode)
{


	return (usage->type == EV_KEY && usage->code == keycode);
}
