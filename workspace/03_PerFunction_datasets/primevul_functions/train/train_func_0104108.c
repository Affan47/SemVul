get_rrset_trust(struct msg_parse* msg, struct rrset_parse* rrset)
{
	uint16_t AA = msg->flags & BIT_AA;
	if(rrset->section == LDNS_SECTION_ANSWER) {
		if(AA) {

			if(msg->rrset_first &&
				msg->rrset_first->section==LDNS_SECTION_ANSWER
				&& msg->rrset_first->type==LDNS_RR_TYPE_CNAME){
				if(rrset == msg->rrset_first)
					return rrset_trust_ans_AA;
				else 	return rrset_trust_ans_noAA;
			}
			if(msg->rrset_first &&
				msg->rrset_first->section==LDNS_SECTION_ANSWER
				&& msg->rrset_first->type==LDNS_RR_TYPE_DNAME){
				if(rrset == msg->rrset_first ||
				   rrset == msg->rrset_first->rrset_all_next)
					return rrset_trust_ans_AA;
				else 	return rrset_trust_ans_noAA;
			}
			return rrset_trust_ans_AA;
		}
		else	return rrset_trust_ans_noAA;
	} else if(rrset->section == LDNS_SECTION_AUTHORITY) {
		if(AA)	return rrset_trust_auth_AA;
		else	return rrset_trust_auth_noAA;
	} else {

		if(AA)	return rrset_trust_add_AA;
		else	return rrset_trust_add_noAA;
	}

	return rrset_trust_none;
}
