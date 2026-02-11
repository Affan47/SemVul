rt73usb_start_queue(struct data_queue *queue)
{
	struct rt2x00_dev *rt2x00dev = queue->rt2x00dev;
	u32 reg;

	switch (queue->qid) {
	case QID_RX:
		rt2x00usb_register_read(rt2x00dev, TXRX_CSR0, &reg);
		rt2x00_set_field32(&reg, TXRX_CSR0_DISABLE_RX, 0);
		rt2x00usb_register_write(rt2x00dev, TXRX_CSR0, reg);
		break;
	case QID_BEACON:
		rt2x00usb_register_read(rt2x00dev, TXRX_CSR9, &reg);
		rt2x00_set_field32(&reg, TXRX_CSR9_TSF_TICKING, 1);
		rt2x00_set_field32(&reg, TXRX_CSR9_TBTT_ENABLE, 1);
		rt2x00_set_field32(&reg, TXRX_CSR9_BEACON_GEN, 1);
		rt2x00usb_register_write(rt2x00dev, TXRX_CSR9, reg);
		break;
	default:
		break;
	}
}
