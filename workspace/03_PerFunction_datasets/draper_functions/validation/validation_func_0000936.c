is_insecure
(const struct blockcipher_desc* c, uint32_t keysize, uint32_t tweaksize)
{
	if (c->insecure)
		return 1;
	if (keysize && c->insecure_key_range) {
		size_t i = 0;
		while(c->insecure_key_range[i].from) {
			if (is_in_range32(&c->insecure_key_range[i],
			keysize))
				return 1;
			i++;
		}
	}
	if (tweaksize && c->insecure_tweak_range) {
		size_t i = 0;
		while(c->insecure_tweak_range[i].from) {
			if (is_in_range32(&c->insecure_tweak_range[i],
			tweaksize))
				return 1;
			i++;
		}
	}
	return 0;
}
