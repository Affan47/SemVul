r600_mmio_hdp_flush(struct radeon_device *rdev)
{


	if ((rdev->family >= CHIP_RV770) && (rdev->family <= CHIP_RV740) &&
	    rdev->vram_scratch.ptr && !(rdev->flags & RADEON_IS_AGP)) {
		void __iomem *ptr = (void *)rdev->vram_scratch.ptr;
		u32 tmp;

		WREG32(HDP_DEBUG1, 0);
		tmp = readl((void __iomem *)ptr);
	} else
		WREG32(R_005480_HDP_MEM_COHERENCY_FLUSH_CNTL, 0x1);
}
