shpc_isr(int irq, void *dev_id)
{
	struct controller *ctrl = (struct controller *)dev_id;
	u32 serr_int, slot_reg, intr_loc, intr_loc2;
	int hp_slot;


	intr_loc = shpc_readl(ctrl, INTR_LOC);
	if (!intr_loc)
		return IRQ_NONE;

	ctrl_dbg(ctrl, "%s: intr_loc = %x\n", __func__, intr_loc);

	if (!shpchp_poll_mode) {


		serr_int = shpc_readl(ctrl, SERR_INTR_ENABLE);
		serr_int |= GLOBAL_INTR_MASK;
		serr_int &= ~SERR_INTR_RSVDZ_MASK;
		shpc_writel(ctrl, SERR_INTR_ENABLE, serr_int);

		intr_loc2 = shpc_readl(ctrl, INTR_LOC);
		ctrl_dbg(ctrl, "%s: intr_loc2 = %x\n", __func__, intr_loc2);
	}

	if (intr_loc & CMD_INTR_PENDING) {


		serr_int = shpc_readl(ctrl, SERR_INTR_ENABLE);
		serr_int &= ~SERR_INTR_RSVDZ_MASK;
		shpc_writel(ctrl, SERR_INTR_ENABLE, serr_int);

		wake_up_interruptible(&ctrl->queue);
	}

	if (!(intr_loc & ~CMD_INTR_PENDING))
		goto out;

	for (hp_slot = 0; hp_slot < ctrl->num_slots; hp_slot++) {

		if (!(intr_loc & SLOT_INTR_PENDING(hp_slot)))
			continue;

		slot_reg = shpc_readl(ctrl, SLOT_REG(hp_slot));
		ctrl_dbg(ctrl, "Slot %x with intr, slot register = %x\n",
			 hp_slot, slot_reg);

		if (slot_reg & MRL_CHANGE_DETECTED)
			shpchp_handle_switch_change(hp_slot, ctrl);

		if (slot_reg & BUTTON_PRESS_DETECTED)
			shpchp_handle_attention_button(hp_slot, ctrl);

		if (slot_reg & PRSNT_CHANGE_DETECTED)
			shpchp_handle_presence_change(hp_slot, ctrl);

		if (slot_reg & (ISO_PFAULT_DETECTED | CON_PFAULT_DETECTED))
			shpchp_handle_power_fault(hp_slot, ctrl);


		slot_reg &= ~SLOT_REG_RSVDZ_MASK;
		shpc_writel(ctrl, SLOT_REG(hp_slot), slot_reg);
	}
 out:
	if (!shpchp_poll_mode) {

		serr_int = shpc_readl(ctrl, SERR_INTR_ENABLE);
		serr_int &= ~(GLOBAL_INTR_MASK | SERR_INTR_RSVDZ_MASK);
		shpc_writel(ctrl, SERR_INTR_ENABLE, serr_int);
	}

	return IRQ_HANDLED;
}
