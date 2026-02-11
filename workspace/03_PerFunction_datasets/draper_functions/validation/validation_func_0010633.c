TRANS_default(void)
{
	control_check(RS_SELECT, "DEFAULT without SELECT", "DEFAULT");

	if (current_ctrl->state)
		THROW("Default case already defined");

	trans_select_break(FALSE);

	current_ctrl->value = 0;
	current_ctrl->state = 1;
}
