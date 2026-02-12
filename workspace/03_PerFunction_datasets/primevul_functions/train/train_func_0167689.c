static void b43_wireless_core_detach(struct b43_wldev *dev)
{


	b43_release_firmware(dev);
	b43_phy_free(dev);
}
