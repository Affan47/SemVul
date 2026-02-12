static int sony_resume(struct hid_device *hdev)
{
	struct sony_sc *sc = hid_get_drvdata(hdev);


	if ((sc->quirks & SIXAXIS_CONTROLLER_USB) ||
		(sc->quirks & NAVIGATION_CONTROLLER_USB)) {
		sixaxis_set_operational_usb(sc->hdev);
		sc->defer_initialization = 1;
	}

	return 0;
}
