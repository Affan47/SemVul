update_history (NemoWindowSlot *slot,
                NemoLocationChangeType type,
                GFile *new_location)
{
        switch (type) {
        case NEMO_LOCATION_CHANGE_STANDARD:
		handle_go_elsewhere (slot, new_location);
                return;
        case NEMO_LOCATION_CHANGE_RELOAD:

                return;
        case NEMO_LOCATION_CHANGE_BACK:
                handle_go_back (slot, new_location);
                return;
        case NEMO_LOCATION_CHANGE_FORWARD:
                handle_go_forward (slot, new_location);
                return;
        }
	g_return_if_fail (FALSE);
}
