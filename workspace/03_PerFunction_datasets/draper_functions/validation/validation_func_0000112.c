b43legacy_controller_restart(struct b43legacy_wldev *dev,
				  const char *reason)
{

	if (b43legacy_status(dev) < B43legacy_STAT_INITIALIZED)
		return;
	b43legacyinfo(dev->wl, "Controller RESET (%s) ...\n", reason);
	ieee80211_queue_work(dev->wl->hw, &dev->restart_work);
}
