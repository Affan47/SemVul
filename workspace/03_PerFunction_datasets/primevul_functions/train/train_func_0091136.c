static void gf_m2ts_process_cat(GF_M2TS_Demuxer *ts, GF_M2TS_SECTION_ES *ses, GF_List *sections, u8 table_id, u16 ex_table_id, u8 version_number, u8 last_section_number, u32 status)
{
	u32 evt_type;


	if (!(status&GF_M2TS_TABLE_END)) return;


	if (status&GF_M2TS_TABLE_REPEAT) {
		if (ts->on_event) ts->on_event(ts, GF_M2TS_EVT_CAT_REPEAT, NULL);
		return;
	}


	evt_type = (status&GF_M2TS_TABLE_UPDATE) ? GF_M2TS_EVT_CAT_UPDATE : GF_M2TS_EVT_CAT_FOUND;
	if (ts->on_event) ts->on_event(ts, evt_type, NULL);
}
