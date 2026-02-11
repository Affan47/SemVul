snd_intel8x0m_update(struct intel8x0m *chip, struct ichdev *ichdev)
{
	unsigned long port = ichdev->reg_offset;
	int civ, i, step;
	int ack = 0;

	civ = igetbyte(chip, port + ICH_REG_OFF_CIV);
	if (civ == ichdev->civ) {

		step = 1;
		ichdev->civ++;
		ichdev->civ &= ICH_REG_LVI_MASK;
	} else {
		step = civ - ichdev->civ;
		if (step < 0)
			step += ICH_REG_LVI_MASK + 1;


		ichdev->civ = civ;
	}

	ichdev->position += step * ichdev->fragsize1;
	ichdev->position %= ichdev->size;
	ichdev->lvi += step;
	ichdev->lvi &= ICH_REG_LVI_MASK;
	iputbyte(chip, port + ICH_REG_OFF_LVI, ichdev->lvi);
	for (i = 0; i < step; i++) {
		ichdev->lvi_frag++;
		ichdev->lvi_frag %= ichdev->frags;
		ichdev->bdbar[ichdev->lvi * 2] = cpu_to_le32(ichdev->physbuf +
							     ichdev->lvi_frag *
							     ichdev->fragsize1);
#if 0
		dev_dbg(chip->card->dev,
			"new: bdbar[%i] = 0x%x [0x%x], prefetch = %i, all = 0x%x, 0x%x\n",
		       ichdev->lvi * 2, ichdev->bdbar[ichdev->lvi * 2],
		       ichdev->bdbar[ichdev->lvi * 2 + 1], inb(ICH_REG_OFF_PIV + port),
		       inl(port + 4), inb(port + ICH_REG_OFF_CR));
#endif
		if (--ichdev->ack == 0) {
			ichdev->ack = ichdev->ack_reload;
			ack = 1;
		}
	}
	if (ack && ichdev->substream) {
		spin_unlock(&chip->reg_lock);
		snd_pcm_period_elapsed(ichdev->substream);
		spin_lock(&chip->reg_lock);
	}
	iputbyte(chip, port + ichdev->roff_sr, ICH_FIFOE | ICH_BCIS | ICH_LVBCI);
}
