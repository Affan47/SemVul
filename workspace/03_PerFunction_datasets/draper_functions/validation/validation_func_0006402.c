xhci_update_device(struct usb_hcd *hcd, struct usb_device *udev)
{
	struct xhci_hcd	*xhci = hcd_to_xhci(hcd);
	int		portnum = udev->portnum - 1;

	if (hcd->speed >= HCD_USB3 || !xhci->sw_lpm_support ||
			!udev->lpm_capable)
		return 0;


	if (!udev->parent || udev->parent->parent ||
			udev->descriptor.bDeviceClass == USB_CLASS_HUB)
		return 0;

	if (xhci->hw_lpm_support == 1 &&
			xhci_check_usb2_port_capability(
				xhci, portnum, XHCI_HLC)) {
		udev->usb2_hw_lpm_capable = 1;
		udev->l1_params.timeout = XHCI_L1_TIMEOUT;
		udev->l1_params.besl = XHCI_DEFAULT_BESL;
		if (xhci_check_usb2_port_capability(xhci, portnum,
					XHCI_BLC))
			udev->usb2_hw_lpm_besl_capable = 1;
	}

	return 0;
}
