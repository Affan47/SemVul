static inline struct iw_spy_data * get_spydata(struct net_device *dev)
{

	if(dev->wireless_data)
		return(dev->wireless_data->spy_data);


	return (dev->priv + dev->wireless_handlers->spy_offset);
}
