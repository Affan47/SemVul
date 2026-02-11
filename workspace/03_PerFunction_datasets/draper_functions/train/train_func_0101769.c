rsxx_eeh_save_issued_creg(struct rsxx_cardinfo *card)
{
	struct creg_cmd *cmd = NULL;

	cmd = card->creg_ctrl.active_cmd;
	card->creg_ctrl.active_cmd = NULL;

	if (cmd) {
		del_timer_sync(&card->creg_ctrl.cmd_timer);

		spin_lock_bh(&card->creg_ctrl.lock);
		list_add(&cmd->list, &card->creg_ctrl.queue);
		card->creg_ctrl.q_depth++;
		card->creg_ctrl.active = 0;
		spin_unlock_bh(&card->creg_ctrl.lock);
	}
}
