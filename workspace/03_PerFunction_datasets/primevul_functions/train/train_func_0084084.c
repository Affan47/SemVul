u32 gf_media_nalu_emulation_bytes_remove_count(const u8 *buffer, u32 nal_size)
{
	u32 i = 0, emulation_bytes_count = 0;
	u8 num_zero = 0;
	if (!buffer || !nal_size) return 0;

	while (i < nal_size)
	{


		if (num_zero == 2
			&& buffer[i] == 0x03
			&& i + 1 < nal_size
			&& (u8)buffer[i + 1] < 0x04)
		{

			num_zero = 0;
			emulation_bytes_count++;
			i++;
		}

		if (!buffer[i])
			num_zero++;
		else
			num_zero = 0;

		i++;
	}

	return emulation_bytes_count;
}
