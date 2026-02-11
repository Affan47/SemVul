btmrvl_check_device_tree(struct btmrvl_private *priv)
{
	struct device_node *dt_node;
	u8 cal_data[BT_CAL_HDR_LEN + BT_CAL_DATA_SIZE];
	int ret;
	u32 val;

	for_each_compatible_node(dt_node, NULL, "btmrvl,cfgdata") {
		ret = of_property_read_u32(dt_node, "btmrvl,gpio-gap", &val);
		if (!ret)
			priv->btmrvl_dev.gpio_gap = val;

		ret = of_property_read_u8_array(dt_node, "btmrvl,cal-data",
						cal_data + BT_CAL_HDR_LEN,
						BT_CAL_DATA_SIZE);
		if (ret) {
			of_node_put(dt_node);
			return ret;
		}

		BT_DBG("Use cal data from device tree");
		ret = btmrvl_download_cal_data(priv, cal_data,
					       BT_CAL_DATA_SIZE);
		if (ret) {
			BT_ERR("Fail to download calibrate data");
			of_node_put(dt_node);
			return ret;
		}
	}

	return 0;
}
