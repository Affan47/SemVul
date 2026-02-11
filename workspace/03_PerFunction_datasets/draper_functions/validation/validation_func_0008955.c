ccdbg_state_save(struct ccdbg *dbg, struct ccstate *state, unsigned int mask)
{
	int	i;

	mask |= CC_STATE_ACC;
	if (mask & CC_STATE_ACC)
		state->acc = ccdbg_execute(dbg, save_acc);
	for (i = 0; i < CC_STATE_NSFR; i++) {
		if (sfrs[i].mask & mask) {
			save_sfr[SAVE_SFR_ADDR] = sfrs[i].address;
			state->sfr[i] = ccdbg_execute(dbg, save_sfr);
		}
	}
	state->mask = mask;
	return 0;
}
