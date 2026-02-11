handle_cursor_read_all(struct vc_data *vc, int command)
{
	int indcount, sentcount, rv, sn;

	switch (command) {
	case RA_NEXT_SENT:

		spk_get_index_count(&indcount, &sentcount);

		spk_reset_index_count(sentcount + 1);
		if (indcount == 1) {
			if (!say_sentence_num(sentcount + 1, 0)) {
				kbd_fakekey2(vc, RA_FIND_NEXT_SENT);
				return;
			}
			synth_insert_next_index(0);
		} else {
			sn = 0;
			if (!say_sentence_num(sentcount + 1, 1)) {
				sn = 1;
				spk_reset_index_count(sn);
			} else
				synth_insert_next_index(0);
			if (!say_sentence_num(sn, 0)) {
				kbd_fakekey2(vc, RA_FIND_NEXT_SENT);
				return;
			}
			synth_insert_next_index(0);
		}
		start_read_all_timer(vc, RA_TIMER);
		break;
	case RA_PREV_SENT:
		break;
	case RA_NEXT_LINE:
		read_all_doc(vc);
		break;
	case RA_PREV_LINE:
		break;
	case RA_DOWN_ARROW:
		if (get_sentence_buf(vc, 0) == -1) {
			kbd_fakekey2(vc, RA_DOWN_ARROW);
		} else {
			say_sentence_num(0, 0);
			synth_insert_next_index(0);
			start_read_all_timer(vc, RA_TIMER);
		}
		break;
	case RA_FIND_NEXT_SENT:
		rv = get_sentence_buf(vc, 0);
		if (rv == -1)
			read_all_doc(vc);
		if (rv == 0)
			kbd_fakekey2(vc, RA_FIND_NEXT_SENT);
		else {
			say_sentence_num(1, 0);
			synth_insert_next_index(0);
			start_read_all_timer(vc, RA_TIMER);
		}
		break;
	case RA_FIND_PREV_SENT:
		break;
	case RA_TIMER:
		spk_get_index_count(&indcount, &sentcount);
		if (indcount < 2)
			kbd_fakekey2(vc, RA_DOWN_ARROW);
		else
			start_read_all_timer(vc, RA_TIMER);
		break;
	}
}
