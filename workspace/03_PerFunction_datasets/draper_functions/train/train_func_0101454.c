kbd_set_state_safe(struct kbd_state *state, struct kbd_state *old)
{
	int ret;

	ret = kbd_set_state(state);
	if (ret == 0)
		return 0;


	if (kbd_set_state(old))
		pr_err("Setting old previous keyboard state failed\n");

	return ret;
}
