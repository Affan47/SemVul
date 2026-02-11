RotateSetRenderable(void *data, Object obj)
{
    RotateData rdata = (RotateData)data;
    DXReference(obj);
    if (rdata->obj)
	DXDelete(rdata->obj);
    rdata->obj = obj;
}
