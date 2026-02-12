static void bw_calcs_data_update_from_pplib(struct dc *dc)
{
	struct dm_pp_clock_levels_with_latency eng_clks = {0};
	struct dm_pp_clock_levels_with_latency mem_clks = {0};
	struct dm_pp_wm_sets_with_clock_ranges clk_ranges = {0};
	struct dm_pp_clock_levels clks = {0};
	int memory_type_multiplier = MEMORY_TYPE_MULTIPLIER_CZ;

	if (dc->bw_vbios && dc->bw_vbios->memory_type == bw_def_hbm)
		memory_type_multiplier = MEMORY_TYPE_HBM;


	if (!dm_pp_get_clock_levels_by_type_with_latency(
			dc->ctx,
			DM_PP_CLOCK_TYPE_ENGINE_CLK,
			&eng_clks)) {


		dm_pp_get_clock_levels_by_type(
				dc->ctx,
				DM_PP_CLOCK_TYPE_ENGINE_CLK,
				&clks);

		dc->bw_vbios->high_sclk = bw_frc_to_fixed(
				clks.clocks_in_khz[clks.num_levels-1], 1000);
		dc->bw_vbios->mid1_sclk  = bw_frc_to_fixed(
				clks.clocks_in_khz[clks.num_levels/8], 1000);
		dc->bw_vbios->mid2_sclk  = bw_frc_to_fixed(
				clks.clocks_in_khz[clks.num_levels*2/8], 1000);
		dc->bw_vbios->mid3_sclk  = bw_frc_to_fixed(
				clks.clocks_in_khz[clks.num_levels*3/8], 1000);
		dc->bw_vbios->mid4_sclk  = bw_frc_to_fixed(
				clks.clocks_in_khz[clks.num_levels*4/8], 1000);
		dc->bw_vbios->mid5_sclk  = bw_frc_to_fixed(
				clks.clocks_in_khz[clks.num_levels*5/8], 1000);
		dc->bw_vbios->mid6_sclk  = bw_frc_to_fixed(
				clks.clocks_in_khz[clks.num_levels*6/8], 1000);
		dc->bw_vbios->low_sclk  = bw_frc_to_fixed(
				clks.clocks_in_khz[0], 1000);


		dm_pp_get_clock_levels_by_type(
				dc->ctx,
				DM_PP_CLOCK_TYPE_MEMORY_CLK,
				&clks);

		dc->bw_vbios->low_yclk = bw_frc_to_fixed(
			clks.clocks_in_khz[0] * memory_type_multiplier, 1000);
		dc->bw_vbios->mid_yclk = bw_frc_to_fixed(
			clks.clocks_in_khz[clks.num_levels>>1] * memory_type_multiplier,
			1000);
		dc->bw_vbios->high_yclk = bw_frc_to_fixed(
			clks.clocks_in_khz[clks.num_levels-1] * memory_type_multiplier,
			1000);

		return;
	}


	dc->bw_vbios->high_sclk = bw_frc_to_fixed(
		eng_clks.data[eng_clks.num_levels-1].clocks_in_khz, 1000);
	dc->bw_vbios->mid1_sclk  = bw_frc_to_fixed(
		eng_clks.data[eng_clks.num_levels/8].clocks_in_khz, 1000);
	dc->bw_vbios->mid2_sclk  = bw_frc_to_fixed(
		eng_clks.data[eng_clks.num_levels*2/8].clocks_in_khz, 1000);
	dc->bw_vbios->mid3_sclk  = bw_frc_to_fixed(
		eng_clks.data[eng_clks.num_levels*3/8].clocks_in_khz, 1000);
	dc->bw_vbios->mid4_sclk  = bw_frc_to_fixed(
		eng_clks.data[eng_clks.num_levels*4/8].clocks_in_khz, 1000);
	dc->bw_vbios->mid5_sclk  = bw_frc_to_fixed(
		eng_clks.data[eng_clks.num_levels*5/8].clocks_in_khz, 1000);
	dc->bw_vbios->mid6_sclk  = bw_frc_to_fixed(
		eng_clks.data[eng_clks.num_levels*6/8].clocks_in_khz, 1000);
	dc->bw_vbios->low_sclk  = bw_frc_to_fixed(
			eng_clks.data[0].clocks_in_khz, 1000);


	dm_pp_get_clock_levels_by_type_with_latency(
			dc->ctx,
			DM_PP_CLOCK_TYPE_MEMORY_CLK,
			&mem_clks);


	dc->bw_vbios->low_yclk = bw_frc_to_fixed(
		mem_clks.data[0].clocks_in_khz * memory_type_multiplier, 1000);
	dc->bw_vbios->mid_yclk = bw_frc_to_fixed(
		mem_clks.data[mem_clks.num_levels>>1].clocks_in_khz * memory_type_multiplier,
		1000);
	dc->bw_vbios->high_yclk = bw_frc_to_fixed(
		mem_clks.data[mem_clks.num_levels-1].clocks_in_khz * memory_type_multiplier,
		1000);


	clk_ranges.num_wm_sets = 4;
	clk_ranges.wm_clk_ranges[0].wm_set_id = WM_SET_A;
	clk_ranges.wm_clk_ranges[0].wm_min_eng_clk_in_khz =
			eng_clks.data[0].clocks_in_khz;
	clk_ranges.wm_clk_ranges[0].wm_max_eng_clk_in_khz =
			eng_clks.data[eng_clks.num_levels*3/8].clocks_in_khz - 1;
	clk_ranges.wm_clk_ranges[0].wm_min_mem_clk_in_khz =
			mem_clks.data[0].clocks_in_khz;
	clk_ranges.wm_clk_ranges[0].wm_max_mem_clk_in_khz =
			mem_clks.data[mem_clks.num_levels>>1].clocks_in_khz - 1;

	clk_ranges.wm_clk_ranges[1].wm_set_id = WM_SET_B;
	clk_ranges.wm_clk_ranges[1].wm_min_eng_clk_in_khz =
			eng_clks.data[eng_clks.num_levels*3/8].clocks_in_khz;

	clk_ranges.wm_clk_ranges[1].wm_max_eng_clk_in_khz = 5000000;
	clk_ranges.wm_clk_ranges[1].wm_min_mem_clk_in_khz =
			mem_clks.data[0].clocks_in_khz;
	clk_ranges.wm_clk_ranges[1].wm_max_mem_clk_in_khz =
			mem_clks.data[mem_clks.num_levels>>1].clocks_in_khz - 1;

	clk_ranges.wm_clk_ranges[2].wm_set_id = WM_SET_C;
	clk_ranges.wm_clk_ranges[2].wm_min_eng_clk_in_khz =
			eng_clks.data[0].clocks_in_khz;
	clk_ranges.wm_clk_ranges[2].wm_max_eng_clk_in_khz =
			eng_clks.data[eng_clks.num_levels*3/8].clocks_in_khz - 1;
	clk_ranges.wm_clk_ranges[2].wm_min_mem_clk_in_khz =
			mem_clks.data[mem_clks.num_levels>>1].clocks_in_khz;

	clk_ranges.wm_clk_ranges[2].wm_max_mem_clk_in_khz = 5000000;

	clk_ranges.wm_clk_ranges[3].wm_set_id = WM_SET_D;
	clk_ranges.wm_clk_ranges[3].wm_min_eng_clk_in_khz =
			eng_clks.data[eng_clks.num_levels*3/8].clocks_in_khz;

	clk_ranges.wm_clk_ranges[3].wm_max_eng_clk_in_khz = 5000000;
	clk_ranges.wm_clk_ranges[3].wm_min_mem_clk_in_khz =
			mem_clks.data[mem_clks.num_levels>>1].clocks_in_khz;

	clk_ranges.wm_clk_ranges[3].wm_max_mem_clk_in_khz = 5000000;


	dm_pp_notify_wm_clock_changes(dc->ctx, &clk_ranges);
}
