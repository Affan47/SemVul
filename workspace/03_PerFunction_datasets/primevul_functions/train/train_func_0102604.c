static void process_deny_list( canon_ace **pp_ace_list )
{
	canon_ace *ace_list = *pp_ace_list;
	canon_ace *curr_ace = NULL;
	canon_ace *curr_ace_next = NULL;


	for (curr_ace = ace_list; curr_ace; curr_ace = curr_ace_next) {
		canon_ace *allow_ace_p;

		curr_ace_next = curr_ace->next;

		if (curr_ace->attr != DENY_ACE)
			continue;

		if (curr_ace->perms == (mode_t)0) {


			DLIST_REMOVE(ace_list, curr_ace);
			continue;
		}

		if (!sid_equal(&curr_ace->trustee, &global_sid_World))
			continue;


		SMB_ASSERT(curr_ace->owner_type == WORLD_ACE);

		if (curr_ace->perms == ALL_ACE_PERMS) {


			canon_ace *prev_entry = curr_ace->prev;

			free_canon_ace_list( curr_ace );
			if (prev_entry)
				prev_entry->next = NULL;
			else {

				ace_list = NULL;
			}
			break;
		}

		for (allow_ace_p = curr_ace->next; allow_ace_p; allow_ace_p = allow_ace_p->next) {


			if (allow_ace_p->attr != ALLOW_ACE)
				continue;

			allow_ace_p->perms &= ~curr_ace->perms;
		}


		DLIST_REMOVE(ace_list, curr_ace);
	}


	for (curr_ace = ace_list; curr_ace; curr_ace = curr_ace_next) {
		mode_t new_perms = (mode_t)0;
		canon_ace *allow_ace_p;

		curr_ace_next = curr_ace->next;

		if (curr_ace->attr != DENY_ACE)
			continue;

		if (curr_ace->owner_type != UID_ACE)
			continue;

		if (curr_ace->perms == ALL_ACE_PERMS) {


			curr_ace->attr = ALLOW_ACE;
			curr_ace->perms = (mode_t)0;
			DLIST_DEMOTE(ace_list, curr_ace, canon_ace *);
			continue;
		}

		for (allow_ace_p = curr_ace->next; allow_ace_p; allow_ace_p = allow_ace_p->next) {

			if (allow_ace_p->attr != ALLOW_ACE)
				continue;


			if (allow_ace_p->owner_type == UID_ACE)
				continue;

			if (uid_entry_in_group( curr_ace, allow_ace_p))
				new_perms |= allow_ace_p->perms;
		}


		curr_ace->attr = ALLOW_ACE;
		curr_ace->perms = (new_perms & ~curr_ace->perms);
		DLIST_DEMOTE(ace_list, curr_ace, canon_ace *);
	}


	for (curr_ace = ace_list; curr_ace; curr_ace = curr_ace_next) {
		canon_ace *allow_ace_p;
		canon_ace *allow_everyone_p = NULL;

		curr_ace_next = curr_ace->next;

		if (curr_ace->attr != DENY_ACE)
			continue;

		if (curr_ace->owner_type != GID_ACE)
			continue;

		for (allow_ace_p = curr_ace->next; allow_ace_p; allow_ace_p = allow_ace_p->next) {

			if (allow_ace_p->attr != ALLOW_ACE)
				continue;


			if (allow_ace_p->owner_type == WORLD_ACE)
				allow_everyone_p = allow_ace_p;


			if (allow_ace_p->owner_type != UID_ACE)
				continue;


			if (uid_entry_in_group( allow_ace_p, curr_ace))
				allow_ace_p->perms &= ~curr_ace->perms;
		}


		curr_ace->attr = ALLOW_ACE;
		if (allow_everyone_p)
			curr_ace->perms = allow_everyone_p->perms & ~curr_ace->perms;
		else
			curr_ace->perms = (mode_t)0;
		DLIST_DEMOTE(ace_list, curr_ace, canon_ace *);
	}


#if 0


	for (curr_ace = ace_list; curr_ace; curr_ace = curr_ace_next) {
		canon_ace *allow_ace_p;

		curr_ace_next = curr_ace->next;

		if (curr_ace->attr != ALLOW_ACE)
			continue;

		if (curr_ace->owner_type != UID_ACE)
			continue;

		for (allow_ace_p = ace_list; allow_ace_p; allow_ace_p = allow_ace_p->next) {

			if (allow_ace_p->attr != ALLOW_ACE)
				continue;


			if (allow_ace_p->owner_type != GID_ACE)
				continue;


			if (uid_entry_in_group( curr_ace, allow_ace_p))
				curr_ace->perms |= allow_ace_p->perms;
		}
	}
#endif

	*pp_ace_list = ace_list;
}
