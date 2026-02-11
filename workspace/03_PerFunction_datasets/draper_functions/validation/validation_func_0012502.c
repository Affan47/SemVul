ubi_get_device(int ubi_num)
{
	struct ubi_device *ubi;

	spin_lock(&ubi_devices_lock);
	ubi = ubi_devices[ubi_num];
	if (ubi) {
		ubi_assert(ubi->ref_count >= 0);
		ubi->ref_count += 1;
		get_device(&ubi->dev);
	}
	spin_unlock(&ubi_devices_lock);

	return ubi;
}
