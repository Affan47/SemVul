WriteAdtsHeader(AP4_ByteStream& output,
                unsigned int    frame_size,
                unsigned int    sampling_frequency_index,
                unsigned int    channel_configuration)
{
	unsigned char bits[7];

	bits[0] = 0xFF;
	bits[1] = 0xF1;
    bits[2] = 0x40 | (sampling_frequency_index << 2) | (channel_configuration >> 2);
    bits[3] = ((channel_configuration&0x3)<<6) | ((frame_size+7) >> 11);
    bits[4] = ((frame_size+7) >> 3)&0xFF;
	bits[5] = (((frame_size+7) << 5)&0xFF) | 0x1F;
	bits[6] = 0xFC;

	return output.Write(bits, 7);


}
