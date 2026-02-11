ipath_set_linkstate(struct ipath_devdata *dd, u8 newstate)
{
	u32 lstate;
	int ret;

	switch (newstate) {
	case IPATH_IB_LINKDOWN_ONLY:
		ipath_set_ib_lstate(dd, INFINIPATH_IBCC_LINKCMD_DOWN, 0);

		ret = 0;
		goto bail;

	case IPATH_IB_LINKDOWN:
		ipath_set_ib_lstate(dd, INFINIPATH_IBCC_LINKCMD_DOWN,
					INFINIPATH_IBCC_LINKINITCMD_POLL);

		ret = 0;
		goto bail;

	case IPATH_IB_LINKDOWN_SLEEP:
		ipath_set_ib_lstate(dd, INFINIPATH_IBCC_LINKCMD_DOWN,
					INFINIPATH_IBCC_LINKINITCMD_SLEEP);

		ret = 0;
		goto bail;

	case IPATH_IB_LINKDOWN_DISABLE:
		ipath_set_ib_lstate(dd, INFINIPATH_IBCC_LINKCMD_DOWN,
					INFINIPATH_IBCC_LINKINITCMD_DISABLE);

		ret = 0;
		goto bail;

	case IPATH_IB_LINKARM:
		if (dd->ipath_flags & IPATH_LINKARMED) {
			ret = 0;
			goto bail;
		}
		if (!(dd->ipath_flags &
		      (IPATH_LINKINIT | IPATH_LINKACTIVE))) {
			ret = -EINVAL;
			goto bail;
		}
		ipath_set_ib_lstate(dd, INFINIPATH_IBCC_LINKCMD_ARMED, 0);


		lstate = IPATH_LINKARMED | IPATH_LINKACTIVE;
		break;

	case IPATH_IB_LINKACTIVE:
		if (dd->ipath_flags & IPATH_LINKACTIVE) {
			ret = 0;
			goto bail;
		}
		if (!(dd->ipath_flags & IPATH_LINKARMED)) {
			ret = -EINVAL;
			goto bail;
		}
		ipath_set_ib_lstate(dd, INFINIPATH_IBCC_LINKCMD_ACTIVE, 0);
		lstate = IPATH_LINKACTIVE;
		break;

	case IPATH_IB_LINK_LOOPBACK:
		dev_info(&dd->pcidev->dev, "Enabling IB local loopback\n");
		dd->ipath_ibcctrl |= INFINIPATH_IBCC_LOOPBACK;
		ipath_write_kreg(dd, dd->ipath_kregs->kr_ibcctrl,
				 dd->ipath_ibcctrl);


		dd->ipath_f_set_ib_cfg(dd, IPATH_IB_CFG_HRTBT,
				       IPATH_IB_HRTBT_OFF);

		ret = 0;
		goto bail;

	case IPATH_IB_LINK_EXTERNAL:
		dev_info(&dd->pcidev->dev,
			"Disabling IB local loopback (normal)\n");
		dd->ipath_f_set_ib_cfg(dd, IPATH_IB_CFG_HRTBT,
				       IPATH_IB_HRTBT_ON);
		dd->ipath_ibcctrl &= ~INFINIPATH_IBCC_LOOPBACK;
		ipath_write_kreg(dd, dd->ipath_kregs->kr_ibcctrl,
				 dd->ipath_ibcctrl);

		ret = 0;
		goto bail;


	case IPATH_IB_LINK_HRTBT:
		ret = dd->ipath_f_set_ib_cfg(dd, IPATH_IB_CFG_HRTBT,
			IPATH_IB_HRTBT_ON);
		goto bail;

	case IPATH_IB_LINK_NO_HRTBT:
		ret = dd->ipath_f_set_ib_cfg(dd, IPATH_IB_CFG_HRTBT,
			IPATH_IB_HRTBT_OFF);
		goto bail;

	default:
		ipath_dbg("Invalid linkstate 0x%x requested\n", newstate);
		ret = -EINVAL;
		goto bail;
	}
	ret = ipath_wait_linkstate(dd, lstate, 2000);

bail:
	return ret;
}
