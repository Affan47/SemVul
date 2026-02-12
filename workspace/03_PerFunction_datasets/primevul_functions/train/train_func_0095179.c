static void av1_decode_frame_wrapup(AV1State *state)
{
	u32 i;
	for (i = 0; i < AV1_NUM_REF_FRAMES; i++) {
		if ((state->frame_state.refresh_frame_flags >> i) & 1) {
			state->RefOrderHint[i] = state->frame_state.order_hint;
			state->SavedGmParams[i] = state->GmParams;
			state->RefFrameType[i] = state->frame_state.frame_type;
		}
	}
	state->frame_state.seen_frame_header = GF_FALSE;

	if ((state->frame_state.show_existing_frame) && (state->frame_state.frame_type == AV1_KEY_FRAME)) {
		state->frame_state.order_hint = state->RefOrderHint[state->frame_state.frame_to_show_map_idx];


		state->GmParams = state->SavedGmParams[state->frame_state.frame_to_show_map_idx];

	}
}
