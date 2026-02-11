r8a66597_hub_control(struct usb_hcd *hcd, u16 typeReq, u16 wValue,
				u16 wIndex, char *buf, u16 wLength)
{
	struct r8a66597 *r8a66597 = hcd_to_r8a66597(hcd);
	int ret;
	int port = (wIndex & 0x00FF) - 1;
	struct r8a66597_root_hub *rh = &r8a66597->root_hub[port];
	unsigned long flags;

	ret = 0;

	spin_lock_irqsave(&r8a66597->lock, flags);
	switch (typeReq) {
	case ClearHubFeature:
	case SetHubFeature:
		switch (wValue) {
		case C_HUB_OVER_CURRENT:
		case C_HUB_LOCAL_POWER:
			break;
		default:
			goto error;
		}
		break;
	case ClearPortFeature:
		if (wIndex > r8a66597->max_root_hub)
			goto error;
		if (wLength != 0)
			goto error;

		switch (wValue) {
		case USB_PORT_FEAT_ENABLE:
			rh->port &= ~USB_PORT_STAT_POWER;
			break;
		case USB_PORT_FEAT_SUSPEND:
			break;
		case USB_PORT_FEAT_POWER:
			r8a66597_port_power(r8a66597, port, 0);
			break;
		case USB_PORT_FEAT_C_ENABLE:
		case USB_PORT_FEAT_C_SUSPEND:
		case USB_PORT_FEAT_C_CONNECTION:
		case USB_PORT_FEAT_C_OVER_CURRENT:
		case USB_PORT_FEAT_C_RESET:
			break;
		default:
			goto error;
		}
		rh->port &= ~(1 << wValue);
		break;
	case GetHubDescriptor:
		r8a66597_hub_descriptor(r8a66597,
					(struct usb_hub_descriptor *)buf);
		break;
	case GetHubStatus:
		*buf = 0x00;
		break;
	case GetPortStatus:
		if (wIndex > r8a66597->max_root_hub)
			goto error;
		*(__le32 *)buf = cpu_to_le32(rh->port);
		break;
	case SetPortFeature:
		if (wIndex > r8a66597->max_root_hub)
			goto error;
		if (wLength != 0)
			goto error;

		switch (wValue) {
		case USB_PORT_FEAT_SUSPEND:
			break;
		case USB_PORT_FEAT_POWER:
			r8a66597_port_power(r8a66597, port, 1);
			rh->port |= USB_PORT_STAT_POWER;
			break;
		case USB_PORT_FEAT_RESET: {
			struct r8a66597_device *dev = rh->dev;

			rh->port |= USB_PORT_STAT_RESET;

			disable_r8a66597_pipe_all(r8a66597, dev);
			free_usb_address(r8a66597, dev, 1);

			r8a66597_mdfy(r8a66597, USBRST, USBRST | UACT,
				      get_dvstctr_reg(port));
			mod_timer(&r8a66597->rh_timer,
				  jiffies + msecs_to_jiffies(50));
			}
			break;
		default:
			goto error;
		}
		rh->port |= 1 << wValue;
		break;
	default:
error:
		ret = -EPIPE;
		break;
	}

	spin_unlock_irqrestore(&r8a66597->lock, flags);
	return ret;
}
