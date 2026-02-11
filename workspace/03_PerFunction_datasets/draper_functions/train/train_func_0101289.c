rt2x00lib_uninitialize(struct rt2x00_dev *rt2x00dev)
{
	if (!test_and_clear_bit(DEVICE_STATE_INITIALIZED, &rt2x00dev->flags))
		return;


	if (rt2x00_has_cap_flag(rt2x00dev, REQUIRE_DELAYED_RFKILL))
		rt2x00rfkill_unregister(rt2x00dev);


	rt2x00dev->ops->lib->uninitialize(rt2x00dev);


	rt2x00queue_uninitialize(rt2x00dev);
}
