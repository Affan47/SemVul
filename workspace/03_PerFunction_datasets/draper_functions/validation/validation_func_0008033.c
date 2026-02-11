_opp_add_static_v2(struct device *dev, struct device_node *np)
{
	struct device_opp *dev_opp;
	struct dev_pm_opp *new_opp;
	u64 rate;
	u32 val;
	int ret;


	mutex_lock(&dev_opp_list_lock);

	new_opp = _allocate_opp(dev, &dev_opp);
	if (!new_opp) {
		ret = -ENOMEM;
		goto unlock;
	}

	ret = of_property_read_u64(np, "opp-hz", &rate);
	if (ret < 0) {
		dev_err(dev, "%s: opp-hz not found\n", __func__);
		goto free_opp;
	}


	new_opp->rate = (unsigned long)rate;
	new_opp->turbo = of_property_read_bool(np, "turbo-mode");

	new_opp->np = np;
	new_opp->dynamic = false;
	new_opp->available = true;

	if (!of_property_read_u32(np, "clock-latency-ns", &val))
		new_opp->clock_latency_ns = val;

	ret = opp_parse_supplies(new_opp, dev);
	if (ret)
		goto free_opp;

	ret = _opp_add(dev, new_opp, dev_opp);
	if (ret)
		goto free_opp;


	if (of_property_read_bool(np, "opp-suspend")) {
		if (dev_opp->suspend_opp)
			dev_warn(dev, "%s: Multiple suspend OPPs found (%lu %lu)\n",
				 __func__, dev_opp->suspend_opp->rate,
				 new_opp->rate);
		else
			dev_opp->suspend_opp = new_opp;
	}

	if (new_opp->clock_latency_ns > dev_opp->clock_latency_ns_max)
		dev_opp->clock_latency_ns_max = new_opp->clock_latency_ns;

	mutex_unlock(&dev_opp_list_lock);

	pr_debug("%s: turbo:%d rate:%lu uv:%lu uvmin:%lu uvmax:%lu latency:%lu\n",
		 __func__, new_opp->turbo, new_opp->rate, new_opp->u_volt,
		 new_opp->u_volt_min, new_opp->u_volt_max,
		 new_opp->clock_latency_ns);


	srcu_notifier_call_chain(&dev_opp->srcu_head, OPP_EVENT_ADD, new_opp);
	return 0;

free_opp:
	_opp_remove(dev_opp, new_opp, false);
unlock:
	mutex_unlock(&dev_opp_list_lock);
	return ret;
}
