static void dualshock4_calibration_work(struct work_struct *work)
{
	struct sony_sc *sc = container_of(work, struct sony_sc, hotplug_worker);
	unsigned long flags;
	enum ds4_dongle_state dongle_state;
	int ret;

	ret = dualshock4_get_calibration_data(sc);
	if (ret < 0) {


		hid_err(sc->hdev, "DualShock 4 USB dongle: calibration failed, disabling device\n");
		dongle_state = DONGLE_DISABLED;
	} else {
		hid_info(sc->hdev, "DualShock 4 USB dongle: calibration completed\n");
		dongle_state = DONGLE_CONNECTED;
	}

	spin_lock_irqsave(&sc->lock, flags);
	sc->ds4_dongle_state = dongle_state;
	spin_unlock_irqrestore(&sc->lock, flags);
}
