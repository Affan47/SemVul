sciport_to_dev(struct isci_port *iport)
{
	int i = iport->physical_port_index;
	struct isci_port *table;
	struct isci_host *ihost;

	if (i == SCIC_SDS_DUMMY_PORT)
		i = SCI_MAX_PORTS+1;

	table = iport - i;
	ihost = container_of(table, typeof(*ihost), ports[0]);

	return &ihost->pdev->dev;
}
