AUDxDAT (int nr, uae_u16 v, uaecptr addr)
{
	struct audio_channel_data *cdp = audio_channel + nr;
	int chan_ena = (dmacon & DMA_MASTER) && (dmacon & (1 << nr));

#if DEBUG_AUDIO > 0
	if (debugchannel (nr) && (DEBUG_AUDIO > 1 || (!chan_ena || addr == 0xffffffff || (cdp->state != 2 && cdp->state != 3)))) {
		write_log (_T("AUD%dDAT: %04X ADDR=%08X LEN=%d/%d %d,%d,%d %06X\n"), nr,
		v, addr, cdp->wlen, cdp->len, cdp->state, chan_ena, isirq (nr) ? 1 : 0, M68K_GETPC);
	}
#endif
	cdp->dat = v;
	cdp->dat_written = true;
#if TEST_AUDIO > 0
	if (debugchannel (nr) && cdp->have_dat)
		write_log (_T("%d: audxdat 1=%04x 2=%04x but old dat not yet used\n"), nr, cdp->dat, cdp->dat2);
	cdp->have_dat = true;
#endif
	if (cdp->state == 2 || cdp->state == 3) {
		if (chan_ena) {
			if (cdp->wlen == 1) {
				cdp->wlen = cdp->len;
				cdp->intreq2 = true;
				if (sampleripper_enabled)
					do_samplerip (cdp);
#if DEBUG_AUDIO > 0
				if (debugchannel (nr) && cdp->wlen > 1)
					write_log (_T("AUD%d looped, IRQ=%d, LC=%08X LEN=%d\n"), nr, isirq (nr) ? 1 : 0, cdp->pt, cdp->wlen);
#endif
			} else {
				cdp->wlen = (cdp->wlen - 1) & 0xffff;
			}
		}
	} else {
		audio_activate ();
		update_audio ();
		audio_state_channel (nr, false);
		schedule_audio ();
		events_schedule ();
	}
	cdp->dat_written = false;
}
