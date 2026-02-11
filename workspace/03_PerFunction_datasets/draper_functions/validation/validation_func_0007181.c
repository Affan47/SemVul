b43legacy_radio_selectchannel(struct b43legacy_wldev *dev,
				  u8 channel,
				  int synthetic_pu_workaround)
{
	struct b43legacy_phy *phy = &dev->phy;

	if (channel == 0xFF) {
		switch (phy->type) {
		case B43legacy_PHYTYPE_B:
		case B43legacy_PHYTYPE_G:
			channel = B43legacy_RADIO_DEFAULT_CHANNEL_BG;
			break;
		default:
			B43legacy_WARN_ON(1);
		}
	}


	if (synthetic_pu_workaround)
		b43legacy_synth_pu_workaround(dev, channel);

	b43legacy_write16(dev, B43legacy_MMIO_CHANNEL,
			  channel2freq_bg(channel));

	if (channel == 14) {
		if (dev->dev->bus->sprom.country_code == 5)
			b43legacy_shm_write32(dev, B43legacy_SHM_SHARED,
					      B43legacy_UCODEFLAGS_OFFSET,
					      b43legacy_shm_read32(dev,
					      B43legacy_SHM_SHARED,
					      B43legacy_UCODEFLAGS_OFFSET)
					      & ~(1 << 7));
		else
			b43legacy_shm_write32(dev, B43legacy_SHM_SHARED,
					      B43legacy_UCODEFLAGS_OFFSET,
					      b43legacy_shm_read32(dev,
					      B43legacy_SHM_SHARED,
					      B43legacy_UCODEFLAGS_OFFSET)
					      | (1 << 7));
		b43legacy_write16(dev, B43legacy_MMIO_CHANNEL_EXT,
				  b43legacy_read16(dev,
				  B43legacy_MMIO_CHANNEL_EXT) | (1 << 11));
	} else
		b43legacy_write16(dev, B43legacy_MMIO_CHANNEL_EXT,
				  b43legacy_read16(dev,
				  B43legacy_MMIO_CHANNEL_EXT) & 0xF7BF);

	phy->channel = channel;


	msleep(8);

	return 0;
}
