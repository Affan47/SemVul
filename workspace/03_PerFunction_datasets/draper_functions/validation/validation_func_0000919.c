b43_get_calib_lo_settings(struct b43_wldev *dev,
					       const struct b43_bbatt *bbatt,
					       const struct b43_rfatt *rfatt)
{
	struct b43_txpower_lo_control *lo = dev->phy.g->lo_control;
	struct b43_lo_calib *c;

	c = b43_find_lo_calib(lo, bbatt, rfatt);
	if (c)
		return c;


	c = b43_calibrate_lo_setting(dev, bbatt, rfatt);
	if (!c)
		return NULL;
	list_add(&c->list, &lo->calib_list);

	return c;
}
