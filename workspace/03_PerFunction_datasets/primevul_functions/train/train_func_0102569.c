static void merge_aces( canon_ace **pp_list_head )
{
	canon_ace *list_head = *pp_list_head;
	canon_ace *curr_ace_outer;
	canon_ace *curr_ace_outer_next;


	for (curr_ace_outer = list_head; curr_ace_outer; curr_ace_outer = curr_ace_outer_next) {
		canon_ace *curr_ace;
		canon_ace *curr_ace_next;

		curr_ace_outer_next = curr_ace_outer->next;

		for (curr_ace = curr_ace_outer->next; curr_ace; curr_ace = curr_ace_next) {

			curr_ace_next = curr_ace->next;

			if (identity_in_ace_equal(curr_ace, curr_ace_outer) &&
				(curr_ace->attr == curr_ace_outer->attr)) {

				if( DEBUGLVL( 10 )) {
					dbgtext("merge_aces: Merging ACE's\n");
					print_canon_ace( curr_ace_outer, 0);
					print_canon_ace( curr_ace, 0);
				}


				curr_ace_outer->perms |= curr_ace->perms;
				DLIST_REMOVE(list_head, curr_ace);
				SAFE_FREE(curr_ace);
				curr_ace_outer_next = curr_ace_outer->next;
			}
		}
	}


	for (curr_ace_outer = list_head; curr_ace_outer; curr_ace_outer = curr_ace_outer_next) {
		canon_ace *curr_ace;
		canon_ace *curr_ace_next;

		curr_ace_outer_next = curr_ace_outer->next;

		for (curr_ace = curr_ace_outer->next; curr_ace; curr_ace = curr_ace_next) {

			curr_ace_next = curr_ace->next;


			if (identity_in_ace_equal(curr_ace, curr_ace_outer) &&
				(curr_ace_outer->attr == DENY_ACE) && (curr_ace->attr == ALLOW_ACE)) {

				if( DEBUGLVL( 10 )) {
					dbgtext("merge_aces: Masking ACE's\n");
					print_canon_ace( curr_ace_outer, 0);
					print_canon_ace( curr_ace, 0);
				}

				curr_ace->perms &= ~curr_ace_outer->perms;

				if (curr_ace->perms == 0) {


					DLIST_REMOVE(list_head, curr_ace);
					SAFE_FREE(curr_ace);
					curr_ace_outer_next = curr_ace_outer->next;

				} else {


					DLIST_REMOVE(list_head, curr_ace_outer);
					SAFE_FREE(curr_ace_outer);
					break;
				}
			}

		}
	}


	*pp_list_head = list_head;
}
