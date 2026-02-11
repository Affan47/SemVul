pidff_needs_set_envelope(struct ff_envelope *envelope,
				    struct ff_envelope *old)
{
	return envelope->attack_level != old->attack_level ||
	       envelope->fade_level != old->fade_level ||
	       envelope->attack_length != old->attack_length ||
	       envelope->fade_length != old->fade_length;
}
