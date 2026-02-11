mt_post_parse(struct mt_device *td)
{
	struct mt_fields *f = td->fields;
	struct mt_class *cls = &td->mtclass;

	if (td->touches_by_report > 0) {
		int field_count_per_touch = f->length / td->touches_by_report;
		td->last_slot_field = f->usages[field_count_per_touch - 1];
	}

	if (td->cc_index < 0)
		cls->quirks &= ~MT_QUIRK_CONTACT_CNT_ACCURATE;
}
