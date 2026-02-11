ide_disable_port(ide_hwif_t *hwif)
{
	struct ide_host *host = hwif->host;
	int i;

	printk(KERN_INFO "%s: disabling port\n", hwif->name);

	for (i = 0; i < MAX_HOST_PORTS; i++) {
		if (host->ports[i] == hwif) {
			host->ports[i] = NULL;
			host->n_ports--;
		}
	}

	ide_port_free(hwif);
}
