int hclge_tm_schd_setup_hw(struct hclge_dev *hdev)
{
	int ret;


	ret = hclge_tm_map_cfg(hdev);
	if (ret)
		return ret;


	ret = hclge_tm_shaper_cfg(hdev);
	if (ret)
		return ret;


	ret = hclge_tm_dwrr_cfg(hdev);
	if (ret)
		return ret;


	return hclge_tm_schd_mode_hw(hdev);
}
