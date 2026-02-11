cik_init_pg(struct radeon_device *rdev)
{
	if (rdev->pg_flags) {
		cik_enable_sck_slowdown_on_pu(rdev, true);
		cik_enable_sck_slowdown_on_pd(rdev, true);
		if (rdev->pg_flags & RADEON_PG_SUPPORT_GFX_PG) {
			cik_init_gfx_cgpg(rdev);
			cik_enable_cp_pg(rdev, true);
			cik_enable_gds_pg(rdev, true);
		}
		cik_init_ao_cu_mask(rdev);
		cik_update_gfx_pg(rdev, true);
	}
}
