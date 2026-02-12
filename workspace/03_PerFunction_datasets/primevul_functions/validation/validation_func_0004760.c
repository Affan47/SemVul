void ndpi_set_protocol_detection_bitmask2(struct ndpi_detection_module_struct *ndpi_str,
                                          const NDPI_PROTOCOL_BITMASK *dbm) {
  NDPI_PROTOCOL_BITMASK detection_bitmask_local;
  NDPI_PROTOCOL_BITMASK *detection_bitmask = &detection_bitmask_local;
  u_int32_t a = 0;

  NDPI_BITMASK_SET(detection_bitmask_local, *dbm);
  NDPI_BITMASK_SET(ndpi_str->detection_bitmask, *dbm);


  ndpi_str->callback_buffer_size = 0;


  init_http_dissector(ndpi_str, &a, detection_bitmask);


  init_starcraft_dissector(ndpi_str, &a, detection_bitmask);


  init_tls_dissector(ndpi_str, &a, detection_bitmask);


  init_stun_dissector(ndpi_str, &a, detection_bitmask);


  init_rtp_dissector(ndpi_str, &a, detection_bitmask);


  init_rtsp_dissector(ndpi_str, &a, detection_bitmask);


  init_rdp_dissector(ndpi_str, &a, detection_bitmask);


  init_sip_dissector(ndpi_str, &a, detection_bitmask);


  init_imo_dissector(ndpi_str, &a, detection_bitmask);


  init_teredo_dissector(ndpi_str, &a, detection_bitmask);


  init_edonkey_dissector(ndpi_str, &a, detection_bitmask);


  init_fasttrack_dissector(ndpi_str, &a, detection_bitmask);


  init_gnutella_dissector(ndpi_str, &a, detection_bitmask);


  init_directconnect_dissector(ndpi_str, &a, detection_bitmask);


  init_nats_dissector(ndpi_str, &a, detection_bitmask);


  init_applejuice_dissector(ndpi_str, &a, detection_bitmask);


  init_soulseek_dissector(ndpi_str, &a, detection_bitmask);


  init_socks_dissector(ndpi_str, &a, detection_bitmask);


  init_irc_dissector(ndpi_str, &a, detection_bitmask);


  init_jabber_dissector(ndpi_str, &a, detection_bitmask);


  init_mail_pop_dissector(ndpi_str, &a, detection_bitmask);


  init_mail_imap_dissector(ndpi_str, &a, detection_bitmask);


  init_mail_smtp_dissector(ndpi_str, &a, detection_bitmask);


  init_usenet_dissector(ndpi_str, &a, detection_bitmask);


  init_dns_dissector(ndpi_str, &a, detection_bitmask);


  init_fbzero_dissector(ndpi_str, &a, detection_bitmask);


  init_vmware_dissector(ndpi_str, &a, detection_bitmask);


  init_non_tcp_udp_dissector(ndpi_str, &a, detection_bitmask);


  init_sopcast_dissector(ndpi_str, &a, detection_bitmask);


  init_tvuplayer_dissector(ndpi_str, &a, detection_bitmask);


  init_ppstream_dissector(ndpi_str, &a, detection_bitmask);


  init_pplive_dissector(ndpi_str, &a, detection_bitmask);


  init_iax_dissector(ndpi_str, &a, detection_bitmask);


  init_mgpc_dissector(ndpi_str, &a, detection_bitmask);


  init_zattoo_dissector(ndpi_str, &a, detection_bitmask);


  init_qq_dissector(ndpi_str, &a, detection_bitmask);


  init_ssh_dissector(ndpi_str, &a, detection_bitmask);


  init_ayiya_dissector(ndpi_str, &a, detection_bitmask);


  init_thunder_dissector(ndpi_str, &a, detection_bitmask);


  init_vnc_dissector(ndpi_str, &a, detection_bitmask);


  init_teamviewer_dissector(ndpi_str, &a, detection_bitmask);


  init_dhcp_dissector(ndpi_str, &a, detection_bitmask);


  init_steam_dissector(ndpi_str, &a, detection_bitmask);


  init_halflife2_dissector(ndpi_str, &a, detection_bitmask);


  init_xbox_dissector(ndpi_str, &a, detection_bitmask);


  init_http_activesync_dissector(ndpi_str, &a, detection_bitmask);


  init_smb_dissector(ndpi_str, &a, detection_bitmask);


  init_mining_dissector(ndpi_str, &a, detection_bitmask);


  init_telnet_dissector(ndpi_str, &a, detection_bitmask);


  init_ntp_dissector(ndpi_str, &a, detection_bitmask);


  init_nfs_dissector(ndpi_str, &a, detection_bitmask);


  init_ssdp_dissector(ndpi_str, &a, detection_bitmask);


  init_world_of_warcraft_dissector(ndpi_str, &a, detection_bitmask);


  init_postgres_dissector(ndpi_str, &a, detection_bitmask);


  init_mysql_dissector(ndpi_str, &a, detection_bitmask);


  init_bgp_dissector(ndpi_str, &a, detection_bitmask);


  init_snmp_dissector(ndpi_str, &a, detection_bitmask);


  init_kontiki_dissector(ndpi_str, &a, detection_bitmask);


  init_icecast_dissector(ndpi_str, &a, detection_bitmask);


  init_shoutcast_dissector(ndpi_str, &a, detection_bitmask);


  init_kerberos_dissector(ndpi_str, &a, detection_bitmask);


  init_openft_dissector(ndpi_str, &a, detection_bitmask);


  init_syslog_dissector(ndpi_str, &a, detection_bitmask);


  init_directdownloadlink_dissector(ndpi_str, &a, detection_bitmask);


  init_netbios_dissector(ndpi_str, &a, detection_bitmask);


  init_mdns_dissector(ndpi_str, &a, detection_bitmask);


  init_ipp_dissector(ndpi_str, &a, detection_bitmask);


  init_ldap_dissector(ndpi_str, &a, detection_bitmask);


  init_warcraft3_dissector(ndpi_str, &a, detection_bitmask);


  init_xdmcp_dissector(ndpi_str, &a, detection_bitmask);


  init_tftp_dissector(ndpi_str, &a, detection_bitmask);


  init_mssql_tds_dissector(ndpi_str, &a, detection_bitmask);


  init_pptp_dissector(ndpi_str, &a, detection_bitmask);


  init_stealthnet_dissector(ndpi_str, &a, detection_bitmask);


  init_dhcpv6_dissector(ndpi_str, &a, detection_bitmask);


  init_afp_dissector(ndpi_str, &a, detection_bitmask);


  init_checkmk_dissector(ndpi_str, &a, detection_bitmask);


  init_aimini_dissector(ndpi_str, &a, detection_bitmask);


  init_florensia_dissector(ndpi_str, &a, detection_bitmask);


  init_maplestory_dissector(ndpi_str, &a, detection_bitmask);


  init_dofus_dissector(ndpi_str, &a, detection_bitmask);


  init_world_of_kung_fu_dissector(ndpi_str, &a, detection_bitmask);


  init_fiesta_dissector(ndpi_str, &a, detection_bitmask);


  init_crossfire_dissector(ndpi_str, &a, detection_bitmask);


  init_guildwars_dissector(ndpi_str, &a, detection_bitmask);


  init_armagetron_dissector(ndpi_str, &a, detection_bitmask);


  init_dropbox_dissector(ndpi_str, &a, detection_bitmask);


  init_spotify_dissector(ndpi_str, &a, detection_bitmask);


  init_radius_dissector(ndpi_str, &a, detection_bitmask);


  init_citrix_dissector(ndpi_str, &a, detection_bitmask);


  init_lotus_notes_dissector(ndpi_str, &a, detection_bitmask);


  init_gtp_dissector(ndpi_str, &a, detection_bitmask);


  init_dcerpc_dissector(ndpi_str, &a, detection_bitmask);


  init_netflow_dissector(ndpi_str, &a, detection_bitmask);


  init_sflow_dissector(ndpi_str, &a, detection_bitmask);


  init_h323_dissector(ndpi_str, &a, detection_bitmask);


  init_openvpn_dissector(ndpi_str, &a, detection_bitmask);


  init_noe_dissector(ndpi_str, &a, detection_bitmask);


  init_ciscovpn_dissector(ndpi_str, &a, detection_bitmask);


  init_teamspeak_dissector(ndpi_str, &a, detection_bitmask);


  init_tor_dissector(ndpi_str, &a, detection_bitmask);


  init_skinny_dissector(ndpi_str, &a, detection_bitmask);


  init_rtcp_dissector(ndpi_str, &a, detection_bitmask);


  init_rsync_dissector(ndpi_str, &a, detection_bitmask);


  init_whois_das_dissector(ndpi_str, &a, detection_bitmask);


  init_oracle_dissector(ndpi_str, &a, detection_bitmask);


  init_corba_dissector(ndpi_str, &a, detection_bitmask);


  init_rtmp_dissector(ndpi_str, &a, detection_bitmask);


  init_ftp_control_dissector(ndpi_str, &a, detection_bitmask);


  init_ftp_data_dissector(ndpi_str, &a, detection_bitmask);


  init_pando_dissector(ndpi_str, &a, detection_bitmask);


  init_megaco_dissector(ndpi_str, &a, detection_bitmask);


  init_redis_dissector(ndpi_str, &a, detection_bitmask);


  init_upnp_dissector(ndpi_str, &a, detection_bitmask);


  init_vhua_dissector(ndpi_str, &a, detection_bitmask);


  init_zmq_dissector(ndpi_str, &a, detection_bitmask);


  init_telegram_dissector(ndpi_str, &a, detection_bitmask);


  init_quic_dissector(ndpi_str, &a, detection_bitmask);


  init_diameter_dissector(ndpi_str, &a, detection_bitmask);


  init_apple_push_dissector(ndpi_str, &a, detection_bitmask);


  init_eaq_dissector(ndpi_str, &a, detection_bitmask);


  init_kakaotalk_voice_dissector(ndpi_str, &a, detection_bitmask);


  init_mpegts_dissector(ndpi_str, &a, detection_bitmask);


  init_ubntac2_dissector(ndpi_str, &a, detection_bitmask);


  init_coap_dissector(ndpi_str, &a, detection_bitmask);


  init_mqtt_dissector(ndpi_str, &a, detection_bitmask);


  init_someip_dissector(ndpi_str, &a, detection_bitmask);


  init_rx_dissector(ndpi_str, &a, detection_bitmask);


  init_git_dissector(ndpi_str, &a, detection_bitmask);


  init_hangout_dissector(ndpi_str, &a, detection_bitmask);


  init_drda_dissector(ndpi_str, &a, detection_bitmask);


  init_bjnp_dissector(ndpi_str, &a, detection_bitmask);


  init_smpp_dissector(ndpi_str, &a, detection_bitmask);


  init_tinc_dissector(ndpi_str, &a, detection_bitmask);


  init_fix_dissector(ndpi_str, &a, detection_bitmask);


  init_nintendo_dissector(ndpi_str, &a, detection_bitmask);


  init_modbus_dissector(ndpi_str, &a, detection_bitmask);


  init_capwap_dissector(ndpi_str, &a, detection_bitmask);


  init_zabbix_dissector(ndpi_str, &a, detection_bitmask);


  init_viber_dissector(ndpi_str, &a, detection_bitmask);


  init_skype_dissector(ndpi_str, &a, detection_bitmask);


  init_bittorrent_dissector(ndpi_str, &a, detection_bitmask);


  init_whatsapp_dissector(ndpi_str, &a, detection_bitmask);


  init_ookla_dissector(ndpi_str, &a, detection_bitmask);


  init_amqp_dissector(ndpi_str, &a, detection_bitmask);


  init_csgo_dissector(ndpi_str, &a, detection_bitmask);


  init_lisp_dissector(ndpi_str, &a, detection_bitmask);


  init_ajp_dissector(ndpi_str, &a, detection_bitmask);


  init_memcached_dissector(ndpi_str, &a, detection_bitmask);


  init_nest_log_sink_dissector(ndpi_str, &a, detection_bitmask);


  init_wireguard_dissector(ndpi_str, &a, detection_bitmask);


  init_amazon_video_dissector(ndpi_str, &a, detection_bitmask);


  init_targus_getdata_dissector(ndpi_str, &a, detection_bitmask);


  init_s7comm_dissector(ndpi_str, &a, detection_bitmask);


  init_104_dissector(ndpi_str, &a, detection_bitmask);


  init_websocket_dissector(ndpi_str, &a, detection_bitmask);

#ifdef CUSTOM_NDPI_PROTOCOLS
#include "../../../nDPI-custom/custom_ndpi_main_init.c"
#endif


  ndpi_str->callback_buffer_size = a;

  NDPI_LOG_DBG2(ndpi_str, "callback_buffer_size is %u\n", ndpi_str->callback_buffer_size);


  ndpi_str->callback_buffer_size_tcp_payload = 0;
  ndpi_str->callback_buffer_size_tcp_no_payload = 0;
  for (a = 0; a < ndpi_str->callback_buffer_size; a++) {
    if((ndpi_str->callback_buffer[a].ndpi_selection_bitmask &
	(NDPI_SELECTION_BITMASK_PROTOCOL_INT_TCP | NDPI_SELECTION_BITMASK_PROTOCOL_INT_TCP_OR_UDP |
	 NDPI_SELECTION_BITMASK_PROTOCOL_COMPLETE_TRAFFIC)) != 0) {
      if(_ndpi_debug_callbacks)
	NDPI_LOG_DBG2(ndpi_str, "callback_buffer_tcp_payload, adding buffer %u as entry %u\n", a,
		      ndpi_str->callback_buffer_size_tcp_payload);

      memcpy(&ndpi_str->callback_buffer_tcp_payload[ndpi_str->callback_buffer_size_tcp_payload],
	     &ndpi_str->callback_buffer[a], sizeof(struct ndpi_call_function_struct));
      ndpi_str->callback_buffer_size_tcp_payload++;

      if((ndpi_str->callback_buffer[a].ndpi_selection_bitmask & NDPI_SELECTION_BITMASK_PROTOCOL_HAS_PAYLOAD) ==
	 0) {
	if(_ndpi_debug_callbacks)
	  NDPI_LOG_DBG2(
                        ndpi_str,
                        "\tcallback_buffer_tcp_no_payload, additional adding buffer %u to no_payload process\n", a);

	memcpy(&ndpi_str->callback_buffer_tcp_no_payload[ndpi_str->callback_buffer_size_tcp_no_payload],
	       &ndpi_str->callback_buffer[a], sizeof(struct ndpi_call_function_struct));
	ndpi_str->callback_buffer_size_tcp_no_payload++;
      }
    }
  }

  ndpi_str->callback_buffer_size_udp = 0;
  for (a = 0; a < ndpi_str->callback_buffer_size; a++) {
    if((ndpi_str->callback_buffer[a].ndpi_selection_bitmask &
	(NDPI_SELECTION_BITMASK_PROTOCOL_INT_UDP | NDPI_SELECTION_BITMASK_PROTOCOL_INT_TCP_OR_UDP |
	 NDPI_SELECTION_BITMASK_PROTOCOL_COMPLETE_TRAFFIC)) != 0) {
      if(_ndpi_debug_callbacks)
	NDPI_LOG_DBG2(ndpi_str, "callback_buffer_size_udp: adding buffer : %u as entry %u\n", a,
		      ndpi_str->callback_buffer_size_udp);

      memcpy(&ndpi_str->callback_buffer_udp[ndpi_str->callback_buffer_size_udp], &ndpi_str->callback_buffer[a],
	     sizeof(struct ndpi_call_function_struct));
      ndpi_str->callback_buffer_size_udp++;
    }
  }

  ndpi_str->callback_buffer_size_non_tcp_udp = 0;
  for (a = 0; a < ndpi_str->callback_buffer_size; a++) {
    if((ndpi_str->callback_buffer[a].ndpi_selection_bitmask &
	(NDPI_SELECTION_BITMASK_PROTOCOL_INT_TCP | NDPI_SELECTION_BITMASK_PROTOCOL_INT_UDP |
	 NDPI_SELECTION_BITMASK_PROTOCOL_INT_TCP_OR_UDP)) == 0 ||
       (ndpi_str->callback_buffer[a].ndpi_selection_bitmask & NDPI_SELECTION_BITMASK_PROTOCOL_COMPLETE_TRAFFIC) !=
       0) {
      if(_ndpi_debug_callbacks)
	NDPI_LOG_DBG2(ndpi_str, "callback_buffer_non_tcp_udp: adding buffer : %u as entry %u\n", a,
		      ndpi_str->callback_buffer_size_non_tcp_udp);

      memcpy(&ndpi_str->callback_buffer_non_tcp_udp[ndpi_str->callback_buffer_size_non_tcp_udp],
	     &ndpi_str->callback_buffer[a], sizeof(struct ndpi_call_function_struct));
      ndpi_str->callback_buffer_size_non_tcp_udp++;
    }
  }
}
