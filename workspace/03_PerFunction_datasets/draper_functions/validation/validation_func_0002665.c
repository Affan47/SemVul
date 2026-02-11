iflinux_get_permanent_mac(struct lldpd *cfg,
    struct interfaces_device_list *interfaces,
    struct interfaces_device *iface)
{
	struct interfaces_device *master;
	int f, state = 0;
	FILE *netbond;
	const char *slaveif = "Slave Interface: ";
	const char *hwaddr = "Permanent HW addr: ";
	u_int8_t mac[ETHER_ADDR_LEN];
	char path[SYSFS_PATH_MAX];
	char line[100];

	if ((master = iface->upper) == NULL || master->type != IFACE_BOND_T)
		return;

	log_debug("interfaces", "get MAC address for %s",
	    iface->name);


	if (snprintf(path, SYSFS_PATH_MAX, "/proc/net/bonding/%s",
		master->name) >= SYSFS_PATH_MAX) {
		log_warnx("interfaces", "path truncated");
		return;
	}
	if ((f = priv_open(path)) < 0) {
		if (snprintf(path, SYSFS_PATH_MAX, "/proc/self/net/bonding/%s",
			master->name) >= SYSFS_PATH_MAX) {
			log_warnx("interfaces", "path truncated");
			return;
		}
		f = priv_open(path);
	}
	if (f < 0) {
		log_warnx("interfaces",
		    "unable to find %s in /proc/net/bonding or /proc/self/net/bonding",
		    master->name);
		return;
	}
	if ((netbond = fdopen(f, "r")) == NULL) {
		log_warn("interfaces", "unable to read stream from %s", path);
		close(f);
		return;
	}


	while (fgets(line, sizeof(line), netbond)) {
		switch (state) {
		case 0:
			if (strncmp(line, slaveif, strlen(slaveif)) == 0) {
				if (line[strlen(line)-1] == '\n')
					line[strlen(line)-1] = '\0';
				if (strcmp(iface->name,
					line + strlen(slaveif)) == 0)
					state++;
			}
			break;
		case 1:
			if (strncmp(line, hwaddr, strlen(hwaddr)) == 0) {
				if (line[strlen(line)-1] == '\n')
					line[strlen(line)-1] = '\0';
				if (sscanf(line + strlen(hwaddr),
					"%02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx",
					&mac[0], &mac[1], &mac[2],
					&mac[3], &mac[4], &mac[5]) !=
				    ETHER_ADDR_LEN) {
					log_warn("interfaces", "unable to parse %s",
					    line + strlen(hwaddr));
					fclose(netbond);
					return;
				}
				memcpy(iface->address, mac,
				    ETHER_ADDR_LEN);
				fclose(netbond);
				return;
			}
			break;
		}
	}
	log_warnx("interfaces", "unable to find real mac address for %s",
	    iface->name);
	fclose(netbond);
}
