ath9k_hw_init(struct ath_hw *ah)
{
	int ret;
	struct ath_common *common = ath9k_hw_common(ah);


	switch (ah->hw_version.devid) {
	case AR5416_DEVID_PCI:
	case AR5416_DEVID_PCIE:
	case AR5416_AR9100_DEVID:
	case AR9160_DEVID_PCI:
	case AR9280_DEVID_PCI:
	case AR9280_DEVID_PCIE:
	case AR9285_DEVID_PCIE:
	case AR9287_DEVID_PCI:
	case AR9287_DEVID_PCIE:
	case AR2427_DEVID_PCIE:
	case AR9300_DEVID_PCIE:
	case AR9300_DEVID_AR9485_PCIE:
	case AR9300_DEVID_AR9340:
		break;
	default:
		if (common->bus_ops->ath_bus_type == ATH_USB)
			break;
		DBG("ath9k: Hardware device ID 0x%04x not supported\n",
			ah->hw_version.devid);
		return -EOPNOTSUPP;
	}

	ret = __ath9k_hw_init(ah);
	if (ret) {
		DBG("ath9k: "
			"Unable to initialize hardware; initialization status: %d\n",
			ret);
		return ret;
	}

	return 0;
}
