static u8 av1_get_qindex(Bool ignoreDeltaQ, u32 segmentId, u32 base_q_idx, u32 delta_q_present, u32 CurrentQIndex, Bool segmentation_enabled, u8 *features_SEG_LVL_ALT_Q_enabled, s32 *features_SEG_LVL_ALT_Q)
{

	if (segmentation_enabled && features_SEG_LVL_ALT_Q_enabled[segmentId]) {

		s32 data = features_SEG_LVL_ALT_Q[segmentId];
		s32 qindex = base_q_idx + data;

		if ((ignoreDeltaQ == 0) && (delta_q_present == 1)) qindex = CurrentQIndex + data;

		if (qindex < 0) return 0;
		else if (qindex > 255) return 255;
		else return (u8)qindex;
	}

	if ((ignoreDeltaQ == 0) && (delta_q_present == 1)) return CurrentQIndex;

	return base_q_idx;
}
