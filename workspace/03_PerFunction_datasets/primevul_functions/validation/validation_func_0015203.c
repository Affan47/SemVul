BOOL license_read_product_info(wStream* s, LICENSE_PRODUCT_INFO* productInfo)
{
	if (Stream_GetRemainingLength(s) < 8)
		return FALSE;

	Stream_Read_UINT32(s, productInfo->dwVersion);
	Stream_Read_UINT32(s, productInfo->cbCompanyName);


	if ((productInfo->cbCompanyName < 2) || (productInfo->cbCompanyName % 2 != 0))
		return FALSE;

	if (Stream_GetRemainingLength(s) < productInfo->cbCompanyName)
		return FALSE;

	productInfo->pbProductId = NULL;
	productInfo->pbCompanyName = (BYTE*)malloc(productInfo->cbCompanyName);
	if (!productInfo->pbCompanyName)
		return FALSE;
	Stream_Read(s, productInfo->pbCompanyName, productInfo->cbCompanyName);

	if (Stream_GetRemainingLength(s) < 4)
		goto out_fail;

	Stream_Read_UINT32(s, productInfo->cbProductId);

	if ((productInfo->cbProductId < 2) || (productInfo->cbProductId % 2 != 0))
		goto out_fail;

	if (Stream_GetRemainingLength(s) < productInfo->cbProductId)
		goto out_fail;

	productInfo->pbProductId = (BYTE*)malloc(productInfo->cbProductId);
	if (!productInfo->pbProductId)
		goto out_fail;
	Stream_Read(s, productInfo->pbProductId, productInfo->cbProductId);
	return TRUE;

out_fail:
	free(productInfo->pbCompanyName);
	free(productInfo->pbProductId);
	productInfo->pbCompanyName = NULL;
	productInfo->pbProductId = NULL;
	return FALSE;
}
