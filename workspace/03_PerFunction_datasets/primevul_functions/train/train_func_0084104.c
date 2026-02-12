u32 gf_media_nalu_remove_emulation_bytes(const u8 *buffer_src, u8 *buffer_dst, u32 nal_size)
{
	u32 i = 0, emulation_bytes_count = 0;
	u8 num_zero = 0;

	while (i < nal_size)
	{


		if (num_zero == 2
			&& buffer_src[i] == 0x03
			&& i + 1 < nal_size
			&& (u8)buffer_src[i + 1] < 0x04)
		{

			num_zero = 0;
			emulation_bytes_count++;
			i++;
		}

		buffer_dst[i - emulation_bytes_count] = buffer_src[i];

		if (!buffer_src[i])
			num_zero++;
		else
			num_zero = 0;

		i++;
	}

	return nal_size - emulation_bytes_count;
}
