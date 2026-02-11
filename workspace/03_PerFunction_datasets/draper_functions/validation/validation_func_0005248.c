nhrp_payload_add_cie(struct nhrp_payload *payload, struct nhrp_cie *cie)
{
	if (payload->payload_type != NHRP_PAYLOAD_TYPE_CIE_LIST) {
		nhrp_cie_free(cie);
		nhrp_info("Trying to add CIE payload to non-CIE payload %d\n",
			  payload->payload_type);
		return;
	}

	list_add_tail(&cie->cie_list_entry, &payload->u.cie_list);
}
