aac_rx_intr_message(int irq, void *dev_id)
{
	int isAif, isFastResponse, isSpecial;
	struct aac_dev *dev = dev_id;
	u32 Index = rx_readl(dev, MUnit.OutboundQueue);
	if (unlikely(Index == 0xFFFFFFFFL))
		Index = rx_readl(dev, MUnit.OutboundQueue);
	if (likely(Index != 0xFFFFFFFFL)) {
		do {
			isAif = isFastResponse = isSpecial = 0;
			if (Index & 0x00000002L) {
				isAif = 1;
				if (Index == 0xFFFFFFFEL)
					isSpecial = 1;
				Index &= ~0x00000002L;
			} else {
				if (Index & 0x00000001L)
					isFastResponse = 1;
				Index >>= 2;
			}
			if (!isSpecial) {
				if (unlikely(aac_intr_normal(dev,
						Index, isAif,
						isFastResponse, NULL))) {
					rx_writel(dev,
						MUnit.OutboundQueue,
						Index);
					rx_writel(dev,
						MUnit.ODR,
						DoorBellAdapterNormRespReady);
				}
			}
			Index = rx_readl(dev, MUnit.OutboundQueue);
		} while (Index != 0xFFFFFFFFL);
		return IRQ_HANDLED;
	}
	return IRQ_NONE;
}
