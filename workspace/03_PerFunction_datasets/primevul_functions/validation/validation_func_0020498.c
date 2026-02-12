static inline u32 hid_report_len(struct hid_report *report)
{

	return ((report->size - 1) >> 3) + 1 + (report->id > 0);
}
