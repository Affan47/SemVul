static void b43_set_slot_time(struct b43_wldev *dev, u16 slot_time)
{


	if (b43_current_band(dev->wl) == IEEE80211_BAND_5GHZ)
		return;
	b43_write16(dev, B43_MMIO_IFSSLOT, 510 + slot_time);


}
