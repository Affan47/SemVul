START_TEST (test_recv_sonmp)
{
	char pkt1[] = {
		0x01, 0x00, 0x81, 0x00, 0x01, 0x00, 0x00, 0x1b,
		0x25, 0x08, 0x50, 0x47, 0x00, 0x13, 0xaa, 0xaa,
		0x03, 0x00, 0x00, 0x81, 0x01, 0xa2, 0xac, 0x10,
		0x65, 0xa8, 0x00, 0x02, 0x08, 0x38, 0x0c, 0x02,
		0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00 };


	struct lldpd_chassis *nchassis = NULL;
	struct lldpd_port *nport = NULL;
	char cid[5];
	in_addr_t ip;

	fail_unless(sonmp_decode(NULL, pkt1, sizeof(pkt1), &hardware,
		&nchassis, &nport) != -1);
	if (!nchassis || !nport) {
		fail("unable to decode packet");
		return;
	}
	ck_assert_int_eq(nchassis->c_id_subtype,
	    LLDP_CHASSISID_SUBTYPE_ADDR);
	ck_assert_int_eq(nchassis->c_id_len, 5);
	cid[0] = 1;
	ip = inet_addr("172.16.101.168");
	memcpy(cid + 1, &ip, sizeof(in_addr_t));
	fail_unless(memcmp(nchassis->c_id, cid, 5) == 0);
	ck_assert_str_eq(nchassis->c_name, "172.16.101.168");
	ck_assert_str_eq(nchassis->c_descr, "Nortel Ethernet Routing 8610 L3 Switch");
	ck_assert_int_eq(TAILQ_FIRST(&nchassis->c_mgmt)->m_addr.inet.s_addr,
	    (u_int32_t)inet_addr("172.16.101.168"));
	ck_assert_int_eq(TAILQ_FIRST(&nchassis->c_mgmt)->m_iface, 0);
	ck_assert_str_eq(nport->p_descr, "port 2/8");
	ck_assert_int_eq(nport->p_id_subtype,
	    LLDP_PORTID_SUBTYPE_LOCAL);
	ck_assert_int_eq(nport->p_id_len, strlen("00-02-08"));
	fail_unless(memcmp(nport->p_id,
		"00-02-08", strlen("00-02-08")) == 0);
	ck_assert_int_eq(nchassis->c_cap_enabled, 0);
}
