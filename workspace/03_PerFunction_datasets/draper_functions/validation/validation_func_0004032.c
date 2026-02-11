ath6kl_recovery_cleanup(struct ath6kl *ar)
{
	if (!ar->fw_recovery.enable)
		return;

	set_bit(RECOVERY_CLEANUP, &ar->flag);

	del_timer_sync(&ar->fw_recovery.hb_timer);
	cancel_work_sync(&ar->fw_recovery.recovery_work);
}
