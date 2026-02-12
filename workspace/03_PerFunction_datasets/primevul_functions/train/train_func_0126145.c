lldp_send(struct lldpd *global OVS_UNUSED,
          struct lldpd_hardware *hardware,
          struct dp_packet *p)
{
    unsigned int orig_size = dp_packet_size(p);
    unsigned int start;

    struct lldpd_port *port;
    struct lldpd_chassis *chassis;
    struct lldpd_mgmt *mgmt;
    const uint8_t avaya[] = LLDP_TLV_ORG_AVAYA;
    struct lldpd_aa_isid_vlan_maps_tlv *vlan_isid_map;
    uint8_t msg_auth_digest[LLDP_TLV_AA_ISID_VLAN_DIGEST_LENGTH];

    port = &hardware->h_lport;
    chassis = port->p_chassis;


    VLOG_DBG("LLDP PDU send to %s mtu %d incoming",
              hardware->h_ifname, hardware->h_mtu);


    lldp_tlv_start(p, LLDP_TLV_CHASSIS_ID, &start);
    lldp_tlv_put_u8(p, chassis->c_id_subtype);
    dp_packet_put(p, chassis->c_id, chassis->c_id_len);
    lldp_tlv_end(p, start);


    lldp_tlv_start(p, LLDP_TLV_PORT_ID, &start);
    lldp_tlv_put_u8(p, port->p_id_subtype);
    dp_packet_put(p, port->p_id, port->p_id_len);
    lldp_tlv_end(p, start);


    lldp_tlv_start(p, LLDP_TLV_TTL, &start);
    lldp_tlv_put_u16(p, chassis->c_ttl);
    lldp_tlv_end(p, start);


    if (chassis->c_name && *chassis->c_name != '\0') {
        lldp_tlv_start(p, LLDP_TLV_SYSTEM_NAME, &start);
        dp_packet_put(p, chassis->c_name, strlen(chassis->c_name));
        lldp_tlv_end(p, start);
    }


    if (chassis->c_descr && *chassis->c_descr != '\0') {
        lldp_tlv_start(p, LLDP_TLV_SYSTEM_DESCR, &start);
        dp_packet_put(p, chassis->c_descr, strlen(chassis->c_descr));
        lldp_tlv_end(p, start);
    }


    lldp_tlv_start(p, LLDP_TLV_SYSTEM_CAP, &start);
    lldp_tlv_put_u16(p, chassis->c_cap_available);
    lldp_tlv_put_u16(p, chassis->c_cap_enabled);
    lldp_tlv_end(p, start);

    LIST_FOR_EACH (mgmt, m_entries, &chassis->c_mgmt) {
        lldp_tlv_start(p, LLDP_TLV_MGMT_ADDR, &start);
        lldp_tlv_put_u8(p, mgmt->m_addrsize + 1);
        lldp_tlv_put_u8(p, lldpd_af_to_lldp_proto(mgmt->m_family));
        dp_packet_put(p, &mgmt->m_addr, mgmt->m_addrsize);


        if (mgmt->m_iface == 0) {

            lldp_tlv_put_u8(p, LLDP_MGMT_IFACE_UNKNOWN);
            lldp_tlv_put_u32(p, 0);
        } else {

            lldp_tlv_put_u8(p, LLDP_MGMT_IFACE_IFINDEX);
            lldp_tlv_put_u32(p, mgmt->m_iface);
        }
        lldp_tlv_put_u8(p, 0);
        lldp_tlv_end(p, start);
    }


    if (port->p_descr && *port->p_descr != '\0') {
        lldp_tlv_start(p, LLDP_TLV_PORT_DESCR, &start);
        dp_packet_put(p, port->p_descr, strlen(port->p_descr));
        lldp_tlv_end(p, start);
    }


    if (port->p_element.type != 0) {
        u_int16_t aa_element_first_word = 0;
        u_int16_t aa_element_second_word = 0;
        u_int16_t aa_element_state = 0;
        u_int8_t aa_elem_sys_id_first_byte;
        u_int8_t aa_elem_sys_id_second_byte;


        aa_element_state = ((port->p_element.vlan_tagging & 0x1) << 5) |
            ((port->p_element.auto_prov_mode & 0x3) << 3);


        aa_element_first_word = (port->p_element.type << 10) |
            (aa_element_state << 4) |
            ((port->p_element.mgmt_vlan & 0x0F00)>> 8);


        aa_element_second_word = (port->p_element.mgmt_vlan & 0xFF) << 8;


        aa_elem_sys_id_first_byte =
            ((port->p_element.system_id.conn_type & 0x7) << 5) |
            ((port->p_element.system_id.rsvd >> 8) & 0x3);


        aa_elem_sys_id_second_byte =
            (port->p_element.system_id.rsvd & 0xFF);

        memset(msg_auth_digest, 0, sizeof msg_auth_digest);

        lldp_tlv_start(p, LLDP_TLV_ORG, &start);
        dp_packet_put(p, avaya, sizeof avaya);
        lldp_tlv_put_u8(p, LLDP_TLV_AA_ELEMENT_SUBTYPE);
        dp_packet_put(p, msg_auth_digest, sizeof msg_auth_digest);
        lldp_tlv_put_u16(p, aa_element_first_word);
        lldp_tlv_put_u16(p, aa_element_second_word);
        dp_packet_put(p, &port->p_element.system_id.system_mac,
                      sizeof port->p_element.system_id.system_mac);
        lldp_tlv_put_u8(p, aa_elem_sys_id_first_byte);
        lldp_tlv_put_u8(p, aa_elem_sys_id_second_byte);
        dp_packet_put(p, &port->p_element.system_id.rsvd2,
                      sizeof port->p_element.system_id.rsvd2);
        lldp_tlv_end(p, start);
    }

    if (!ovs_list_is_empty(&port->p_isid_vlan_maps)) {

        memset(msg_auth_digest, 0, sizeof msg_auth_digest);

        lldp_tlv_start(p, LLDP_TLV_ORG, &start);
        dp_packet_put(p, avaya, sizeof avaya);
        lldp_tlv_put_u8(p, LLDP_TLV_AA_ISID_VLAN_ASGNS_SUBTYPE);
        dp_packet_put(p, msg_auth_digest, sizeof msg_auth_digest);

        LIST_FOR_EACH (vlan_isid_map,
                       m_entries,
                       &hardware->h_lport.p_isid_vlan_maps) {
            u_int16_t status_vlan_word;
            status_vlan_word =
                (vlan_isid_map->isid_vlan_data.status << 12) |
                vlan_isid_map->isid_vlan_data.vlan;

            lldp_tlv_put_u16(p, status_vlan_word);
            lldp_tlv_put_isid(p, vlan_isid_map->isid_vlan_data.isid);
        }

        lldp_tlv_end(p, start);
    }


    lldp_tlv_start(p, LLDP_TLV_END, &start);
    lldp_tlv_end(p, start);

    hardware->h_tx_cnt++;

    const char *lldp = dp_packet_at_assert(p, orig_size, 0);
    unsigned int lldp_len = dp_packet_size(p) - orig_size;
    if (!hardware->h_lport.p_lastframe
        || hardware->h_lport.p_lastframe->size != lldp_len
        || memcmp(hardware->h_lport.p_lastframe->frame, lldp, lldp_len)) {

        struct lldpd_frame *frame = xmalloc(sizeof *frame + lldp_len);
        frame->size = lldp_len;
        memcpy(frame->frame, lldp, lldp_len);
        free(hardware->h_lport.p_lastframe);
        hardware->h_lport.p_lastframe = frame;
        hardware->h_lport.p_lastchange = time(NULL);
    }

    return dp_packet_size(p);
}
