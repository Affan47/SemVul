nv31_mpeg_init(struct nvkm_engine *mpeg)
{
	struct nvkm_subdev *subdev = &mpeg->subdev;
	struct nvkm_device *device = subdev->device;


	nvkm_wr32(device, 0x00b0e0, 0x00000020);
	nvkm_wr32(device, 0x00b0e8, 0x00000020);


	nvkm_wr32(device, 0x00b32c, 0x00000000);
	nvkm_wr32(device, 0x00b314, 0x00000100);
	nvkm_wr32(device, 0x00b220, 0x00000031);
	nvkm_wr32(device, 0x00b300, 0x02001ec1);
	nvkm_mask(device, 0x00b32c, 0x00000001, 0x00000001);

	nvkm_wr32(device, 0x00b100, 0xffffffff);
	nvkm_wr32(device, 0x00b140, 0xffffffff);

	if (nvkm_msec(device, 2000,
		if (!(nvkm_rd32(device, 0x00b200) & 0x00000001))
			break;
	) < 0) {
		nvkm_error(subdev, "timeout %08x\n",
			   nvkm_rd32(device, 0x00b200));
		return -EBUSY;
	}

	return 0;
}
