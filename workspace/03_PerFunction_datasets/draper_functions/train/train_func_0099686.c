hci_link_policy(uint16_t ocf, int plen, uint8_t *data)
{
	const uint16_t ogf = OGF_INFO_PARAM;

	switch (ocf) {
	default:
		command_status(ogf, ocf, 0x01);
		break;
	}
}
