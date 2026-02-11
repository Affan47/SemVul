synaptics_query_modes(struct psmouse *psmouse)
{
	struct synaptics_data *priv = psmouse->private;
	unsigned char bid[3];


	if (SYN_ID_FULL(priv->identity) < 0x705)
		return 0;

	if (synaptics_send_cmd(psmouse, SYN_QUE_MODES, bid))
		return -1;
	priv->board_id = ((bid[0] & 0xfc) << 6) | bid[1];

	if (SYN_MEXT_CAP_BIT(bid[0]))
		return synaptics_more_extended_queries(psmouse);

	return 0;
}
