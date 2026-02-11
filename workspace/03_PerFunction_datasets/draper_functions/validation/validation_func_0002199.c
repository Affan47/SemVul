vi_set_ip_blocks(struct amdgpu_device *adev)
{
	switch (adev->asic_type) {
	case CHIP_TOPAZ:
		adev->ip_blocks = topaz_ip_blocks;
		adev->num_ip_blocks = ARRAY_SIZE(topaz_ip_blocks);
		break;
	case CHIP_FIJI:
		adev->ip_blocks = fiji_ip_blocks;
		adev->num_ip_blocks = ARRAY_SIZE(fiji_ip_blocks);
		break;
	case CHIP_TONGA:
		adev->ip_blocks = tonga_ip_blocks;
		adev->num_ip_blocks = ARRAY_SIZE(tonga_ip_blocks);
		break;
	case CHIP_CARRIZO:
	case CHIP_STONEY:
		adev->ip_blocks = cz_ip_blocks;
		adev->num_ip_blocks = ARRAY_SIZE(cz_ip_blocks);
		break;
	default:

		return -EINVAL;
	}

	return 0;
}
