get_last_last_pattern()
{
	if (LIKELY(comp->pattern_count > 1))
		return comp->pattern[comp->pattern_count - 2];
	else
		return NULL_PATTERN;
}
