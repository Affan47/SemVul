hotkey_notify_wakeup(const u32 hkey,
				 bool *send_acpi_ev,
				 bool *ignore_acpi_ev)
{

	*send_acpi_ev = true;
	*ignore_acpi_ev = false;

	switch (hkey) {
	case TP_HKEY_EV_WKUP_S3_UNDOCK:
	case TP_HKEY_EV_WKUP_S4_UNDOCK:
		hotkey_wakeup_reason = TP_ACPI_WAKEUP_UNDOCK;
		*ignore_acpi_ev = true;
		break;

	case TP_HKEY_EV_WKUP_S3_BAYEJ:
	case TP_HKEY_EV_WKUP_S4_BAYEJ:
		hotkey_wakeup_reason = TP_ACPI_WAKEUP_BAYEJ;
		*ignore_acpi_ev = true;
		break;

	case TP_HKEY_EV_WKUP_S3_BATLOW:
	case TP_HKEY_EV_WKUP_S4_BATLOW:
		pr_alert("EMERGENCY WAKEUP: battery almost empty\n");


		break;

	default:
		return false;
	}

	if (hotkey_wakeup_reason != TP_ACPI_WAKEUP_NONE) {
		pr_info("woke up due to a hot-unplug request...\n");
		hotkey_wakeup_reason_notify_change();
	}
	return true;
}
