gf100_grctx_mmio_item(struct gf100_grctx *info, u32 addr, u32 data,
		      int shift, int buffer)
{
	struct nvkm_device *device = info->gr->base.engine.subdev.device;
	if (info->data) {
		if (shift >= 0) {
			info->mmio->addr = addr;
			info->mmio->data = data;
			info->mmio->shift = shift;
			info->mmio->buffer = buffer;
			if (buffer >= 0)
				data |= info->buffer[buffer] >> shift;
			info->mmio++;
		} else
			return;
	} else {
		if (buffer >= 0)
			return;
	}

	nvkm_wr32(device, addr, data);
}
