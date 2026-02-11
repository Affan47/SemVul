nv04_timer_intr(struct nvkm_timer *tmr)
{
	struct nvkm_subdev *subdev = &tmr->subdev;
	struct nvkm_device *device = subdev->device;
	u32 stat = nvkm_rd32(device, NV04_PTIMER_INTR_0);

	if (stat & 0x00000001) {
		nvkm_wr32(device, NV04_PTIMER_INTR_0, 0x00000001);
		nvkm_timer_alarm_trigger(tmr);
		stat &= ~0x00000001;
	}

	if (stat) {
		nvkm_error(subdev, "intr %08x\n", stat);
		nvkm_wr32(device, NV04_PTIMER_INTR_0, stat);
	}
}
