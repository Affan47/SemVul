tg3_phy_pull_config(struct tg3 *tp)
{
	int err;
	u32 val;

	err = tg3_readphy(tp, MII_BMCR, &val);
	if (err)
		goto done;

	if (!(val & BMCR_ANENABLE)) {
		tp->link_config.autoneg = AUTONEG_DISABLE;
		tp->link_config.advertising = 0;
		tg3_flag_clear(tp, PAUSE_AUTONEG);

		err = -EIO;

		switch (val & (BMCR_SPEED1000 | BMCR_SPEED100)) {
		case 0:
			if (tp->phy_flags & TG3_PHYFLG_ANY_SERDES)
				goto done;

			tp->link_config.speed = SPEED_10;
			break;
		case BMCR_SPEED100:
			if (tp->phy_flags & TG3_PHYFLG_ANY_SERDES)
				goto done;

			tp->link_config.speed = SPEED_100;
			break;
		case BMCR_SPEED1000:
			if (!(tp->phy_flags & TG3_PHYFLG_10_100_ONLY)) {
				tp->link_config.speed = SPEED_1000;
				break;
			}

		default:
			goto done;
		}

		if (val & BMCR_FULLDPLX)
			tp->link_config.duplex = DUPLEX_FULL;
		else
			tp->link_config.duplex = DUPLEX_HALF;

		tp->link_config.flowctrl = FLOW_CTRL_RX | FLOW_CTRL_TX;

		err = 0;
		goto done;
	}

	tp->link_config.autoneg = AUTONEG_ENABLE;
	tp->link_config.advertising = ADVERTISED_Autoneg;
	tg3_flag_set(tp, PAUSE_AUTONEG);

	if (!(tp->phy_flags & TG3_PHYFLG_ANY_SERDES)) {
		u32 adv;

		err = tg3_readphy(tp, MII_ADVERTISE, &val);
		if (err)
			goto done;

		adv = mii_adv_to_ethtool_adv_t(val & ADVERTISE_ALL);
		tp->link_config.advertising |= adv | ADVERTISED_TP;

		tp->link_config.flowctrl = tg3_decode_flowctrl_1000T(val);
	} else {
		tp->link_config.advertising |= ADVERTISED_FIBRE;
	}

	if (!(tp->phy_flags & TG3_PHYFLG_10_100_ONLY)) {
		u32 adv;

		if (!(tp->phy_flags & TG3_PHYFLG_ANY_SERDES)) {
			err = tg3_readphy(tp, MII_CTRL1000, &val);
			if (err)
				goto done;

			adv = mii_ctrl1000_to_ethtool_adv_t(val);
		} else {
			err = tg3_readphy(tp, MII_ADVERTISE, &val);
			if (err)
				goto done;

			adv = tg3_decode_flowctrl_1000X(val);
			tp->link_config.flowctrl = adv;

			val &= (ADVERTISE_1000XHALF | ADVERTISE_1000XFULL);
			adv = mii_adv_to_ethtool_adv_x(val);
		}

		tp->link_config.advertising |= adv;
	}

done:
	return err;
}
