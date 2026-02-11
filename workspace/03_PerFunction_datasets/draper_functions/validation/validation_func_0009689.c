gf_cm_lock_input(GF_CompositionMemory *cb, u32 TS, Bool codec_reordering)
{
#if !NO_TEMPORAL_SCALABLE
	GF_CMUnit *cu;
	if (codec_reordering) {
#endif

		if (cb->input->dataLength) {
			if (cb->input->TS==TS)
				return cb->input;
			return NULL;
		}
		cb->input->TS = TS;
		return cb->input;

#if !NO_TEMPORAL_SCALABLE
	}


	cu = cb->input;
	while (1) {
		if (cu->TS == TS)
			return cu;
		cu = cu->prev;
		if (cu == cb->input) break;
	}

	cu = cb->input;
	while (1) {
		if (!cu->dataLength) {
			assert(!cu->TS || (cb->Capacity==1));
			cu->TS = TS;
			return cu;
		}
		cu = cu->next;
		if (cu == cb->input) return NULL;
	}
	return NULL;
#endif
}
