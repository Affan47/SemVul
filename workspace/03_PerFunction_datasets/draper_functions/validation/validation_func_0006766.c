scif_display_message(struct scif_dev *scifdev, struct scifmsg *msg,
		     const char *label)
{
	if (!scif_info.en_msg_log)
		return;
	if (msg->uop > SCIF_MAX_MSG) {
		dev_err(&scifdev->sdev->dev,
			"%s: unknown msg type %d\n", label, msg->uop);
		return;
	}
	dev_info(&scifdev->sdev->dev,
		 "%s: msg type %s, src %d:%d, dest %d:%d payload 0x%llx:0x%llx:0x%llx:0x%llx\n",
		 label, message_types[msg->uop], msg->src.node, msg->src.port,
		 msg->dst.node, msg->dst.port, msg->payload[0], msg->payload[1],
		 msg->payload[2], msg->payload[3]);
}
