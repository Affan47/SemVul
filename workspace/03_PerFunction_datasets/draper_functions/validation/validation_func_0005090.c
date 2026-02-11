say_char(struct vc_data *vc)
{
	u_short ch;

	spk_old_attr = spk_attr;
	ch = get_char(vc, (u_short *) spk_pos, &spk_attr);
	if (spk_attr != spk_old_attr) {
		if (spk_attrib_bleep & 1)
			bleep(spk_y);
		if (spk_attrib_bleep & 2)
			say_attributes(vc);
	}
	speak_char(ch & 0xff);
}
