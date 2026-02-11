amdgpu_atombios_is_voltage_gpio(struct amdgpu_device *adev,
				u8 voltage_type, u8 voltage_mode)
{
	int index = GetIndexIntoMasterTable(DATA, VoltageObjectInfo);
	u8 frev, crev;
	u16 data_offset, size;
	union voltage_object_info *voltage_info;

	if (amdgpu_atom_parse_data_header(adev->mode_info.atom_context, index, &size,
				   &frev, &crev, &data_offset)) {
		voltage_info = (union voltage_object_info *)
			(adev->mode_info.atom_context->bios + data_offset);

		switch (frev) {
		case 3:
			switch (crev) {
			case 1:
				if (amdgpu_atombios_lookup_voltage_object_v3(&voltage_info->v3,
								  voltage_type, voltage_mode))
					return true;
				break;
			default:
				DRM_ERROR("unknown voltage object table\n");
				return false;
			}
			break;
		default:
			DRM_ERROR("unknown voltage object table\n");
			return false;
		}

	}
	return false;
}
