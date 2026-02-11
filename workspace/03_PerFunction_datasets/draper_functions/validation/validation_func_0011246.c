mxs_lradc_handle_irq(int irq, void *data)
{
	struct iio_dev *iio = data;
	struct mxs_lradc *lradc = iio_priv(iio);
	unsigned long reg = readl(lradc->base + LRADC_CTRL1);
	u32 clr_irq = mxs_lradc_irq_mask(lradc);
	const u32 ts_irq_mask =
		LRADC_CTRL1_TOUCH_DETECT_IRQ |
		LRADC_CTRL1_LRADC_IRQ(TOUCHSCREEN_VCHANNEL1) |
		LRADC_CTRL1_LRADC_IRQ(TOUCHSCREEN_VCHANNEL2);

	if (!(reg & mxs_lradc_irq_mask(lradc)))
		return IRQ_NONE;

	if (lradc->use_touchscreen && (reg & ts_irq_mask)) {
		mxs_lradc_handle_touch(lradc);


		clr_irq &= ~(LRADC_CTRL1_LRADC_IRQ(TOUCHSCREEN_VCHANNEL1) |
				LRADC_CTRL1_LRADC_IRQ(TOUCHSCREEN_VCHANNEL2));
	}

	if (iio_buffer_enabled(iio)) {
		if (reg & lradc->buffer_vchans)
			iio_trigger_poll(iio->trig);
	} else if (reg & LRADC_CTRL1_LRADC_IRQ(0)) {
		complete(&lradc->completion);
	}

	mxs_lradc_reg_clear(lradc, reg & clr_irq, LRADC_CTRL1);

	return IRQ_HANDLED;
}
