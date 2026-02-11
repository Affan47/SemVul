uc_mgr_free_sequence_element(struct sequence_element *seq)
{
	if (seq == NULL)
		return;
	switch (seq->type) {
	case SEQUENCE_ELEMENT_TYPE_CSET:
	case SEQUENCE_ELEMENT_TYPE_EXEC:
		free(seq->data.exec);
		break;
	default:
		break;
	}
	free(seq);
}
