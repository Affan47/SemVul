static void b43_bcma_remove(struct bcma_device *core)
{
	struct b43_wldev *wldev = bcma_get_drvdata(core);
	struct b43_wl *wl = wldev->wl;


	cancel_work_sync(&wldev->restart_work);
	cancel_work_sync(&wl->firmware_load);

	B43_WARN_ON(!wl);
	if (!wldev->fw.ucode.data)
		return;
	if (wl->current_dev == wldev && wl->hw_registred) {
		b43_leds_stop(wldev);
		ieee80211_unregister_hw(wl->hw);
	}

	b43_one_core_detach(wldev->dev);

	b43_leds_unregister(wl);

	ieee80211_free_hw(wl->hw);
}
