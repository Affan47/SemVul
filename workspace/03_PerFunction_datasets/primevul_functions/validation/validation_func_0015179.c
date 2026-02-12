static void mcba_usb_process_rx(struct mcba_priv *priv,
				struct mcba_usb_msg *msg)
{
	switch (msg->cmd_id) {
	case MBCA_CMD_I_AM_ALIVE_FROM_CAN:
		mcba_usb_process_ka_can(priv,
					(struct mcba_usb_msg_ka_can *)msg);
		break;

	case MBCA_CMD_I_AM_ALIVE_FROM_USB:
		mcba_usb_process_ka_usb(priv,
					(struct mcba_usb_msg_ka_usb *)msg);
		break;

	case MBCA_CMD_RECEIVE_MESSAGE:
		mcba_usb_process_can(priv, (struct mcba_usb_msg_can *)msg);
		break;

	case MBCA_CMD_NOTHING_TO_SEND:


		break;

	case MBCA_CMD_TRANSMIT_MESSAGE_RSP:

		break;

	default:
		netdev_warn(priv->netdev, "Unsupported msg (0x%hhX)",
			    msg->cmd_id);
		break;
	}
}
