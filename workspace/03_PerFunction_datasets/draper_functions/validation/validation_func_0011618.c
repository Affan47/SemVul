entry_match_by_id(entry_t *entry, ike_sa_id_t *id)
{
	if (id->equals(id, entry->ike_sa_id))
	{
		return TRUE;
	}
	if ((id->get_responder_spi(id) == 0 ||
		 entry->ike_sa_id->get_responder_spi(entry->ike_sa_id) == 0) &&
		id->get_initiator_spi(id) == entry->ike_sa_id->get_initiator_spi(entry->ike_sa_id))
	{

		return TRUE;
	}
	return FALSE;
}
