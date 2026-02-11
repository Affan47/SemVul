handle_button_press_event(struct slot *p_slot)
{
	u8 getstatus;
	struct controller *ctrl = p_slot->ctrl;

	switch (p_slot->state) {
	case STATIC_STATE:
		p_slot->hpc_ops->get_power_status(p_slot, &getstatus);
		if (getstatus) {
			p_slot->state = BLINKINGOFF_STATE;
			ctrl_info(ctrl, "PCI slot #%s - powering off due to button press\n",
				  slot_name(p_slot));
		} else {
			p_slot->state = BLINKINGON_STATE;
			ctrl_info(ctrl, "PCI slot #%s - powering on due to button press\n",
				  slot_name(p_slot));
		}

		p_slot->hpc_ops->green_led_blink(p_slot);
		p_slot->hpc_ops->set_attention_status(p_slot, 0);

		queue_delayed_work(p_slot->wq, &p_slot->work, 5*HZ);
		break;
	case BLINKINGOFF_STATE:
	case BLINKINGON_STATE:


		ctrl_info(ctrl, "Button cancel on Slot(%s)\n",
			  slot_name(p_slot));
		cancel_delayed_work(&p_slot->work);
		if (p_slot->state == BLINKINGOFF_STATE)
			p_slot->hpc_ops->green_led_on(p_slot);
		else
			p_slot->hpc_ops->green_led_off(p_slot);
		p_slot->hpc_ops->set_attention_status(p_slot, 0);
		ctrl_info(ctrl, "PCI slot #%s - action canceled due to button press\n",
			  slot_name(p_slot));
		p_slot->state = STATIC_STATE;
		break;
	case POWEROFF_STATE:
	case POWERON_STATE:


		ctrl_info(ctrl, "Button ignore on Slot(%s)\n",
			  slot_name(p_slot));
		update_slot_info(p_slot);
		break;
	default:
		ctrl_warn(ctrl, "Not a valid state\n");
		break;
	}
}
