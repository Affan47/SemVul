fsl_edma_remove(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct fsl_edma_engine *fsl_edma = platform_get_drvdata(pdev);
	int i;

	of_dma_controller_free(np);
	dma_async_device_unregister(&fsl_edma->dma_dev);

	for (i = 0; i < DMAMUX_NR; i++)
		clk_disable_unprepare(fsl_edma->muxclk[i]);

	return 0;
}
