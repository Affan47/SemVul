tvp7002_get_pdata(struct i2c_client *client)
{
	struct v4l2_of_endpoint bus_cfg;
	struct tvp7002_config *pdata;
	struct device_node *endpoint;
	unsigned int flags;

	if (!IS_ENABLED(CONFIG_OF) || !client->dev.of_node)
		return client->dev.platform_data;

	endpoint = of_graph_get_next_endpoint(client->dev.of_node, NULL);
	if (!endpoint)
		return NULL;

	pdata = devm_kzalloc(&client->dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata)
		goto done;

	v4l2_of_parse_endpoint(endpoint, &bus_cfg);
	flags = bus_cfg.bus.parallel.flags;

	if (flags & V4L2_MBUS_HSYNC_ACTIVE_HIGH)
		pdata->hs_polarity = 1;

	if (flags & V4L2_MBUS_VSYNC_ACTIVE_HIGH)
		pdata->vs_polarity = 1;

	if (flags & V4L2_MBUS_PCLK_SAMPLE_RISING)
		pdata->clk_polarity = 1;

	if (flags & V4L2_MBUS_FIELD_EVEN_HIGH)
		pdata->fid_polarity = 1;

	if (flags & V4L2_MBUS_VIDEO_SOG_ACTIVE_HIGH)
		pdata->sog_polarity = 1;

done:
	of_node_put(endpoint);
	return pdata;
}
