do_control_char()
{
	u8 index = (cur_char < MAX_CONTROL_CODE ? control_map[cur_char] : 0);
	const Sequence *seq = control_sequences + index;

	if (!index && esc_state != ESnormal && cur_char) {
		seq = escape_sequences + (cur_char < MAX_ESCAPE_CODE ? escape_map[esc_state][cur_char] : 0);
	}

	if (seq->action) (this->*(seq->action))();
	if (seq->next != ESkeep) esc_state = seq->next;
}
