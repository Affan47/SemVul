mlxsw_pci_wqe_frag_map(struct mlxsw_pci *mlxsw_pci, char *wqe,
				  int index, char *frag_data, size_t frag_len,
				  int direction)
{
	struct pci_dev *pdev = mlxsw_pci->pdev;
	dma_addr_t mapaddr;

	mapaddr = pci_map_single(pdev, frag_data, frag_len, direction);
	if (unlikely(pci_dma_mapping_error(pdev, mapaddr))) {
		dev_err_ratelimited(&pdev->dev, "failed to dma map tx frag\n");
		return -EIO;
	}
	mlxsw_pci_wqe_address_set(wqe, index, mapaddr);
	mlxsw_pci_wqe_byte_count_set(wqe, index, frag_len);
	return 0;
}
