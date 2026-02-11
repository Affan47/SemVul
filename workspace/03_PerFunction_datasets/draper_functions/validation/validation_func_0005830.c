smaction(Packet *p)
{
    if (_use_anno)
	_ethh.ether_vlan_tci = VLAN_TCI_ANNO(p);
    if ((_ethh.ether_vlan_tci & htons(0x0FFF)) == _native_vlan) {
	if (WritablePacket *q = p->push_mac_header(sizeof(click_ether))) {
	    memcpy(q->data(), &_ethh, 12);
	    q->ether_header()->ether_type = _ethh.ether_vlan_encap_proto;
	    return q;
	} else
	    return 0;
    }
    if (WritablePacket *q = p->push_mac_header(sizeof(click_ether_vlan))) {
	memcpy(q->data(), &_ethh, sizeof(click_ether_vlan));
	return q;
    } else
	return 0;
}
