show_rev(int type, const unsigned char *sha1, const char *name)
{
	if (!(filter & DO_REVS))
		return;
	def = NULL;

	if ((symbolic || abbrev_ref) && name) {
		if (symbolic == SHOW_SYMBOLIC_FULL || abbrev_ref) {
			unsigned char discard[20];
			char *full;

			switch (dwim_ref(name, strlen(name), discard, &full)) {
			case 0:


				break;
			case 1:
				if (abbrev_ref)
					full = shorten_unambiguous_ref(full,
						abbrev_ref_strict);
				show_with_type(type, full);
				break;
			default:
				error("refname '%s' is ambiguous", name);
				break;
			}
		} else {
			show_with_type(type, name);
		}
	}
	else if (abbrev)
		show_with_type(type, find_unique_abbrev(sha1, abbrev));
	else
		show_with_type(type, sha1_to_hex(sha1));
}
