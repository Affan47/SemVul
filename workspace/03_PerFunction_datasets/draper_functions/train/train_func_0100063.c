wl1271_tm_cmd_set_plt_mode(struct wl1271 *wl, struct nlattr *tb[])
{
	u32 val;
	int ret;

	wl1271_debug(DEBUG_TESTMODE, "testmode cmd set plt mode");

	if (!tb[WL1271_TM_ATTR_PLT_MODE])
		return -EINVAL;

	val = nla_get_u32(tb[WL1271_TM_ATTR_PLT_MODE]);

	switch (val) {
	case PLT_OFF:
		ret = wl1271_plt_stop(wl);
		break;
	case PLT_ON:
	case PLT_CHIP_AWAKE:
		ret = wl1271_plt_start(wl, val);
		break;
	case PLT_FEM_DETECT:
		ret = wl1271_tm_detect_fem(wl, tb);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}
