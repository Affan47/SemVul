isdn_tty_readmodem(void)
{
	int resched = 0;
	int midx;
	int i;
	int r;
	modem_info *info;

	for (i = 0; i < ISDN_MAX_CHANNELS; i++) {
		midx = dev->m_idx[i];
		if (midx < 0)
			continue;

		info = &dev->mdm.info[midx];
		if (!info->online)
			continue;

		r = 0;
#ifdef CONFIG_ISDN_AUDIO
		isdn_audio_eval_dtmf(info);
		if ((info->vonline & 1) && (info->emu.vpar[1]))
			isdn_audio_eval_silence(info);
#endif
		if (info->mcr & UART_MCR_RTS) {

			if (!(info->emu.mdmreg[REG_CPPP] & BIT_CPPP))
				r = isdn_readbchan_tty(info->isdn_driver,
						info->isdn_channel,
						&info->port, 0);
			else
				r = isdn_readbchan_tty(info->isdn_driver,
						info->isdn_channel,
						&info->port, 1);
			if (r)
				tty_flip_buffer_push(&info->port);
		} else
			r = 1;

		if (r) {
			info->rcvsched = 0;
			resched = 1;
		} else
			info->rcvsched = 1;
	}
	if (!resched)
		isdn_timer_ctrl(ISDN_TIMER_MODEMREAD, 0);
}
