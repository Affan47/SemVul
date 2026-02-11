adi_read(struct adi_port *port)
{
	int i;
	int result = 0;

	adi_read_packet(port);
	adi_move_bits(port, port->adi[0].length);

	for (i = 0; i < 2; i++)
		if (port->adi[i].length)
			 result |= adi_decode(port->adi + i);

	return result;
}
