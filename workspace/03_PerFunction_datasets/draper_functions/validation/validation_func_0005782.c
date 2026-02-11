packet_bandwidth(unsigned int max_payload_bytes, int speed)
{
	unsigned int bytes, s400_bytes;


	bytes = 3 * 4 + ALIGN(max_payload_bytes, 4);


	if (speed <= SCODE_400)
		s400_bytes = bytes * (1 << (SCODE_400 - speed));
	else
		s400_bytes = DIV_ROUND_UP(bytes, 1 << (speed - SCODE_400));

	return s400_bytes;
}
