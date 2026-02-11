_dxfCleanup(CubesIIInterpolator ci)
{
    if (ci->fieldInterpolator.localized)
    {
	if (ci->nbrs)
	    DXFreeArrayDataLocal(ci->nbrsArray, (Pointer)ci->nbrs);
    }

    if (ci->dHandle)
    {
	DXFreeArrayHandle(ci->dHandle);
	ci->dHandle = NULL;
    }

    if (ci->pHandle)
    {
	DXFreeArrayHandle(ci->pHandle);
	ci->pHandle = NULL;
    }

    if (ci->cHandle)
    {
	DXFreeArrayHandle(ci->cHandle);
	ci->cHandle = NULL;
    }

    DXFree((Pointer)ci->visited);

    _dxfFreeSearchGrid(ci->grid);
}
