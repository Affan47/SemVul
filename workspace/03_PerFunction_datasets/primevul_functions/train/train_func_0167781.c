static void b43_periodic_every30sec(struct b43_wldev *dev)
{

	b43_calculate_link_quality(dev);
}
