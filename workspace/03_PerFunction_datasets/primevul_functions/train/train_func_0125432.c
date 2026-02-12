int bnxt_re_modify_device(struct ib_device *ibdev,
			  int device_modify_mask,
			  struct ib_device_modify *device_modify)
{
	switch (device_modify_mask) {
	case IB_DEVICE_MODIFY_SYS_IMAGE_GUID:


		break;
	case IB_DEVICE_MODIFY_NODE_DESC:

		break;
	default:
		break;
	}
	return 0;
}
