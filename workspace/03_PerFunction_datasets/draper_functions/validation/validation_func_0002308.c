cdtext_is_empty(Cdtext *cdtext)
{
	for (; PTI_END != cdtext->pti; cdtext++) {
		if (NULL != cdtext->value) {
			return -1;
		}
	}

	return 0;
}
