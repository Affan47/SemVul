setup_rss(struct adapter *adapter)
{
	int pidx;

	for_each_port(adapter, pidx) {
		struct port_info *pi = adap2pinfo(adapter, pidx);
		struct sge_eth_rxq *rxq = &adapter->sge.ethrxq[pi->first_qset];
		u16 rss[MAX_PORT_QSETS];
		int qs, err;

		for (qs = 0; qs < pi->nqsets; qs++)
			rss[qs] = rxq[qs].rspq.abs_id;

		err = t4vf_config_rss_range(adapter, pi->viid,
					    0, pi->rss_size, rss, pi->nqsets);
		if (err)
			return err;


		switch (adapter->params.rss.mode) {
		case FW_RSS_GLB_CONFIG_CMD_MODE_BASICVIRTUAL:


			if (!adapter->params.rss.u.basicvirtual.tnlalllookup) {
				union rss_vi_config config;
				err = t4vf_read_rss_vi_config(adapter,
							      pi->viid,
							      &config);
				if (err)
					return err;
				config.basicvirtual.defaultq =
					rxq[0].rspq.abs_id;
				err = t4vf_write_rss_vi_config(adapter,
							       pi->viid,
							       &config);
				if (err)
					return err;
			}
			break;
		}
	}

	return 0;
}
