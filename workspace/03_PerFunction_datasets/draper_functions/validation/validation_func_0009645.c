cs46xx_src_link(struct snd_cs46xx *chip, struct dsp_scb_descriptor * src)
{
	struct dsp_spos_instance * ins = chip->dsp_spos_instance;
	struct dsp_scb_descriptor * parent_scb;

	if (snd_BUG_ON(src->parent_scb_ptr))
		return -EINVAL;
	if (snd_BUG_ON(!ins->master_mix_scb))
		return -EINVAL;

	if (ins->master_mix_scb->sub_list_ptr != ins->the_null_scb) {
		parent_scb = find_next_free_scb (chip,ins->master_mix_scb->sub_list_ptr);
		parent_scb->next_scb_ptr = src;
	} else {
		parent_scb = ins->master_mix_scb;
		parent_scb->sub_list_ptr = src;
	}

	src->parent_scb_ptr = parent_scb;


	cs46xx_dsp_spos_update_scb(chip,parent_scb);

	return 0;
}
