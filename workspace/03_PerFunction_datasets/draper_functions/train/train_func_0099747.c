warn_if_differ_considerably(struct drbd_device *device,
	const char *s, sector_t a, sector_t b)
{
	sector_t d;
	if (a == 0 || b == 0)
		return;
	d = (a > b) ? (a - b) : (b - a);
	if (d > (a>>3) || d > (b>>3))
		drbd_warn(device, "Considerable difference in %s: %llus vs. %llus\n", s,
		     (unsigned long long)a, (unsigned long long)b);
}
