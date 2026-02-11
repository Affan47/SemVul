lanai_buf_deallocate(struct lanai_buffer *buf,
	struct pci_dev *pci)
{
	if (buf->start != NULL) {
		dma_free_coherent(&pci->dev, lanai_buf_size(buf),
				  buf->start, buf->dmaaddr);
		buf->start = buf->end = buf->ptr = NULL;
	}
}
