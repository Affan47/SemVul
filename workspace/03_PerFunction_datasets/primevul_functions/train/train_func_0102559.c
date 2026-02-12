static void add_or_replace_ace(SEC_ACE *nt_ace_list, size_t *num_aces,
				const DOM_SID *sid, enum security_ace_type type,
				uint32_t mask, uint8_t flags)
{
	int i;


	for (i = 0; i < *num_aces; i++) {
		if (sid_equal(&nt_ace_list[i].trustee, sid) &&
		    (nt_ace_list[i].flags == flags)) break;
	}

	if (i < *num_aces) {
		nt_ace_list[i].type = type;
		nt_ace_list[i].access_mask = mask;
		DEBUG(10, ("Replacing ACE %d with SID %s and flags %02x\n",
			   i, sid_string_dbg(sid), flags));
		return;
	}


	init_sec_ace(&nt_ace_list[(*num_aces)++], sid, type, mask, flags);
}
