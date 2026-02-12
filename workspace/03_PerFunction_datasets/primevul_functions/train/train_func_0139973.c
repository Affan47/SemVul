static int bnx2x_init_hw_common(struct bnx2x *bp)
{
	u32 val;

	DP(NETIF_MSG_HW, "starting common init  func %d\n", BP_ABS_FUNC(bp));


	bnx2x_acquire_hw_lock(bp, HW_LOCK_RESOURCE_RESET);

	bnx2x_reset_common(bp);
	REG_WR(bp, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_1_SET, 0xffffffff);

	val = 0xfffc;
	if (CHIP_IS_E3(bp)) {
		val |= MISC_REGISTERS_RESET_REG_2_MSTAT0;
		val |= MISC_REGISTERS_RESET_REG_2_MSTAT1;
	}
	REG_WR(bp, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_2_SET, val);

	bnx2x_release_hw_lock(bp, HW_LOCK_RESOURCE_RESET);

	bnx2x_init_block(bp, BLOCK_MISC, PHASE_COMMON);

	if (!CHIP_IS_E1x(bp)) {
		u8 abs_func_id;


		for (abs_func_id = BP_PATH(bp);
		     abs_func_id < E2_FUNC_MAX*2; abs_func_id += 2) {
			if (abs_func_id == BP_ABS_FUNC(bp)) {
				REG_WR(bp,
				    PGLUE_B_REG_INTERNAL_PFID_ENABLE_MASTER,
				    1);
				continue;
			}

			bnx2x_pretend_func(bp, abs_func_id);

			bnx2x_pf_disable(bp);
			bnx2x_pretend_func(bp, BP_ABS_FUNC(bp));
		}
	}

	bnx2x_init_block(bp, BLOCK_PXP, PHASE_COMMON);
	if (CHIP_IS_E1(bp)) {


		REG_WR(bp, PXP_REG_PXP_INT_MASK_0, 0);
	}

	bnx2x_init_block(bp, BLOCK_PXP2, PHASE_COMMON);
	bnx2x_init_pxp(bp);
	bnx2x_set_endianity(bp);
	bnx2x_ilt_init_page_size(bp, INITOP_SET);

	if (CHIP_REV_IS_FPGA(bp) && CHIP_IS_E1H(bp))
		REG_WR(bp, PXP2_REG_PGL_TAGS_LIMIT, 0x1);


	msleep(100);

	val = REG_RD(bp, PXP2_REG_RQ_CFG_DONE);
	if (val != 1) {
		BNX2X_ERR("PXP2 CFG failed\n");
		return -EBUSY;
	}
	val = REG_RD(bp, PXP2_REG_RD_INIT_DONE);
	if (val != 1) {
		BNX2X_ERR("PXP2 RD_INIT failed\n");
		return -EBUSY;
	}


	if (!CHIP_IS_E1x(bp)) {


		struct ilt_client_info ilt_cli;
		struct bnx2x_ilt ilt;
		memset(&ilt_cli, 0, sizeof(struct ilt_client_info));
		memset(&ilt, 0, sizeof(struct bnx2x_ilt));


		ilt_cli.start = 0;
		ilt_cli.end = ILT_NUM_PAGE_ENTRIES - 1;
		ilt_cli.client_num = ILT_CLIENT_TM;


		bnx2x_pretend_func(bp, (BP_PATH(bp) + 6));
		bnx2x_ilt_client_init_op_ilt(bp, &ilt, &ilt_cli, INITOP_CLEAR);
		bnx2x_pretend_func(bp, BP_ABS_FUNC(bp));

		REG_WR(bp, PXP2_REG_RQ_DRAM_ALIGN, BNX2X_PXP_DRAM_ALIGN);
		REG_WR(bp, PXP2_REG_RQ_DRAM_ALIGN_RD, BNX2X_PXP_DRAM_ALIGN);
		REG_WR(bp, PXP2_REG_RQ_DRAM_ALIGN_SEL, 1);
	}

	REG_WR(bp, PXP2_REG_RQ_DISABLE_INPUTS, 0);
	REG_WR(bp, PXP2_REG_RD_DISABLE_INPUTS, 0);

	if (!CHIP_IS_E1x(bp)) {
		int factor = CHIP_REV_IS_EMUL(bp) ? 1000 :
				(CHIP_REV_IS_FPGA(bp) ? 400 : 0);
		bnx2x_init_block(bp, BLOCK_PGLUE_B, PHASE_COMMON);

		bnx2x_init_block(bp, BLOCK_ATC, PHASE_COMMON);


		do {
			msleep(200);
			val = REG_RD(bp, ATC_REG_ATC_INIT_DONE);
		} while (factor-- && (val != 1));

		if (val != 1) {
			BNX2X_ERR("ATC_INIT failed\n");
			return -EBUSY;
		}
	}

	bnx2x_init_block(bp, BLOCK_DMAE, PHASE_COMMON);

	bnx2x_iov_init_dmae(bp);


	bp->dmae_ready = 1;
	bnx2x_init_fill(bp, TSEM_REG_PRAM, 0, 8, 1);

	bnx2x_init_block(bp, BLOCK_TCM, PHASE_COMMON);

	bnx2x_init_block(bp, BLOCK_UCM, PHASE_COMMON);

	bnx2x_init_block(bp, BLOCK_CCM, PHASE_COMMON);

	bnx2x_init_block(bp, BLOCK_XCM, PHASE_COMMON);

	bnx2x_read_dmae(bp, XSEM_REG_PASSIVE_BUFFER, 3);
	bnx2x_read_dmae(bp, CSEM_REG_PASSIVE_BUFFER, 3);
	bnx2x_read_dmae(bp, TSEM_REG_PASSIVE_BUFFER, 3);
	bnx2x_read_dmae(bp, USEM_REG_PASSIVE_BUFFER, 3);

	bnx2x_init_block(bp, BLOCK_QM, PHASE_COMMON);


	bnx2x_qm_init_ptr_table(bp, bp->qm_cid_count, INITOP_SET);


	REG_WR(bp, QM_REG_SOFT_RESET, 1);
	REG_WR(bp, QM_REG_SOFT_RESET, 0);

	if (CNIC_SUPPORT(bp))
		bnx2x_init_block(bp, BLOCK_TM, PHASE_COMMON);

	bnx2x_init_block(bp, BLOCK_DORQ, PHASE_COMMON);

	if (!CHIP_REV_IS_SLOW(bp))

		REG_WR(bp, DORQ_REG_DORQ_INT_MASK, 0);

	bnx2x_init_block(bp, BLOCK_BRB1, PHASE_COMMON);

	bnx2x_init_block(bp, BLOCK_PRS, PHASE_COMMON);
	REG_WR(bp, PRS_REG_A_PRSU_20, 0xf);

	if (!CHIP_IS_E1(bp))
		REG_WR(bp, PRS_REG_E1HOV_MODE, bp->path_has_ovlan);

	if (!CHIP_IS_E1x(bp) && !CHIP_IS_E3B0(bp)) {
		if (IS_MF_AFEX(bp)) {


			REG_WR(bp, PRS_REG_HDRS_AFTER_BASIC, 0xE);
			REG_WR(bp, PRS_REG_MUST_HAVE_HDRS, 0xA);
			REG_WR(bp, PRS_REG_HDRS_AFTER_TAG_0, 0x6);
			REG_WR(bp, PRS_REG_TAG_ETHERTYPE_0, 0x8926);
			REG_WR(bp, PRS_REG_TAG_LEN_0, 0x4);
		} else {


			REG_WR(bp, PRS_REG_HDRS_AFTER_BASIC,
			       bp->path_has_ovlan ? 7 : 6);
		}
	}

	bnx2x_init_block(bp, BLOCK_TSDM, PHASE_COMMON);
	bnx2x_init_block(bp, BLOCK_CSDM, PHASE_COMMON);
	bnx2x_init_block(bp, BLOCK_USDM, PHASE_COMMON);
	bnx2x_init_block(bp, BLOCK_XSDM, PHASE_COMMON);

	if (!CHIP_IS_E1x(bp)) {

		REG_WR(bp, TSEM_REG_FAST_MEMORY + VFC_REG_MEMORIES_RST,
			   VFC_MEMORIES_RST_REG_CAM_RST |
			   VFC_MEMORIES_RST_REG_RAM_RST);
		REG_WR(bp, XSEM_REG_FAST_MEMORY + VFC_REG_MEMORIES_RST,
			   VFC_MEMORIES_RST_REG_CAM_RST |
			   VFC_MEMORIES_RST_REG_RAM_RST);

		msleep(20);
	}

	bnx2x_init_block(bp, BLOCK_TSEM, PHASE_COMMON);
	bnx2x_init_block(bp, BLOCK_USEM, PHASE_COMMON);
	bnx2x_init_block(bp, BLOCK_CSEM, PHASE_COMMON);
	bnx2x_init_block(bp, BLOCK_XSEM, PHASE_COMMON);


	REG_WR(bp, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_1_CLEAR,
	       0x80000000);
	REG_WR(bp, GRCBASE_MISC + MISC_REGISTERS_RESET_REG_1_SET,
	       0x80000000);

	bnx2x_init_block(bp, BLOCK_UPB, PHASE_COMMON);
	bnx2x_init_block(bp, BLOCK_XPB, PHASE_COMMON);
	bnx2x_init_block(bp, BLOCK_PBF, PHASE_COMMON);

	if (!CHIP_IS_E1x(bp)) {
		if (IS_MF_AFEX(bp)) {


			REG_WR(bp, PBF_REG_HDRS_AFTER_BASIC, 0xE);
			REG_WR(bp, PBF_REG_MUST_HAVE_HDRS, 0xA);
			REG_WR(bp, PBF_REG_HDRS_AFTER_TAG_0, 0x6);
			REG_WR(bp, PBF_REG_TAG_ETHERTYPE_0, 0x8926);
			REG_WR(bp, PBF_REG_TAG_LEN_0, 0x4);
		} else {
			REG_WR(bp, PBF_REG_HDRS_AFTER_BASIC,
			       bp->path_has_ovlan ? 7 : 6);
		}
	}

	REG_WR(bp, SRC_REG_SOFT_RST, 1);

	bnx2x_init_block(bp, BLOCK_SRC, PHASE_COMMON);

	if (CNIC_SUPPORT(bp)) {
		REG_WR(bp, SRC_REG_KEYSEARCH_0, 0x63285672);
		REG_WR(bp, SRC_REG_KEYSEARCH_1, 0x24b8f2cc);
		REG_WR(bp, SRC_REG_KEYSEARCH_2, 0x223aef9b);
		REG_WR(bp, SRC_REG_KEYSEARCH_3, 0x26001e3a);
		REG_WR(bp, SRC_REG_KEYSEARCH_4, 0x7ae91116);
		REG_WR(bp, SRC_REG_KEYSEARCH_5, 0x5ce5230b);
		REG_WR(bp, SRC_REG_KEYSEARCH_6, 0x298d8adf);
		REG_WR(bp, SRC_REG_KEYSEARCH_7, 0x6eb0ff09);
		REG_WR(bp, SRC_REG_KEYSEARCH_8, 0x1830f82f);
		REG_WR(bp, SRC_REG_KEYSEARCH_9, 0x01e46be7);
	}
	REG_WR(bp, SRC_REG_SOFT_RST, 0);

	if (sizeof(union cdu_context) != 1024)

		dev_alert(&bp->pdev->dev,
			  "please adjust the size of cdu_context(%ld)\n",
			  (long)sizeof(union cdu_context));

	bnx2x_init_block(bp, BLOCK_CDU, PHASE_COMMON);
	val = (4 << 24) + (0 << 12) + 1024;
	REG_WR(bp, CDU_REG_CDU_GLOBAL_PARAMS, val);

	bnx2x_init_block(bp, BLOCK_CFC, PHASE_COMMON);
	REG_WR(bp, CFC_REG_INIT_REG, 0x7FF);

	REG_WR(bp, CFC_REG_CFC_INT_MASK, 0);


	REG_WR(bp, CFC_REG_DEBUG0, 0x20020000);

	bnx2x_init_block(bp, BLOCK_HC, PHASE_COMMON);

	if (!CHIP_IS_E1x(bp) && BP_NOMCP(bp))
		REG_WR(bp, IGU_REG_RESET_MEMORIES, 0x36);

	bnx2x_init_block(bp, BLOCK_IGU, PHASE_COMMON);
	bnx2x_init_block(bp, BLOCK_MISC_AEU, PHASE_COMMON);


	REG_WR(bp, 0x2814, 0xffffffff);
	REG_WR(bp, 0x3820, 0xffffffff);

	if (!CHIP_IS_E1x(bp)) {
		REG_WR(bp, PCICFG_OFFSET + PXPCS_TL_CONTROL_5,
			   (PXPCS_TL_CONTROL_5_ERR_UNSPPORT1 |
				PXPCS_TL_CONTROL_5_ERR_UNSPPORT));
		REG_WR(bp, PCICFG_OFFSET + PXPCS_TL_FUNC345_STAT,
			   (PXPCS_TL_FUNC345_STAT_ERR_UNSPPORT4 |
				PXPCS_TL_FUNC345_STAT_ERR_UNSPPORT3 |
				PXPCS_TL_FUNC345_STAT_ERR_UNSPPORT2));
		REG_WR(bp, PCICFG_OFFSET + PXPCS_TL_FUNC678_STAT,
			   (PXPCS_TL_FUNC678_STAT_ERR_UNSPPORT7 |
				PXPCS_TL_FUNC678_STAT_ERR_UNSPPORT6 |
				PXPCS_TL_FUNC678_STAT_ERR_UNSPPORT5));
	}

	bnx2x_init_block(bp, BLOCK_NIG, PHASE_COMMON);
	if (!CHIP_IS_E1(bp)) {

		if (!CHIP_IS_E3(bp))
			REG_WR(bp, NIG_REG_LLH_MF_MODE, IS_MF(bp));
	}
	if (CHIP_IS_E1H(bp))

		REG_WR(bp, NIG_REG_LLH_E1HOV_MODE, IS_MF_SD(bp));

	if (CHIP_REV_IS_SLOW(bp))
		msleep(200);


	val = reg_poll(bp, CFC_REG_LL_INIT_DONE, 1, 100, 10);
	if (val != 1) {
		BNX2X_ERR("CFC LL_INIT failed\n");
		return -EBUSY;
	}
	val = reg_poll(bp, CFC_REG_AC_INIT_DONE, 1, 100, 10);
	if (val != 1) {
		BNX2X_ERR("CFC AC_INIT failed\n");
		return -EBUSY;
	}
	val = reg_poll(bp, CFC_REG_CAM_INIT_DONE, 1, 100, 10);
	if (val != 1) {
		BNX2X_ERR("CFC CAM_INIT failed\n");
		return -EBUSY;
	}
	REG_WR(bp, CFC_REG_DEBUG0, 0);

	if (CHIP_IS_E1(bp)) {


		bnx2x_read_dmae(bp, NIG_REG_STAT2_BRB_OCTET, 2);
		val = *bnx2x_sp(bp, wb_data[0]);


		if ((val == 0) && bnx2x_int_mem_test(bp)) {
			BNX2X_ERR("internal mem self test failed\n");
			return -EBUSY;
		}
	}

	bnx2x_setup_fan_failure_detection(bp);


	REG_RD(bp, PXP2_REG_PXP2_INT_STS_CLR_0);

	bnx2x_enable_blocks_attention(bp);
	bnx2x_enable_blocks_parity(bp);

	if (!BP_NOMCP(bp)) {
		if (CHIP_IS_E1x(bp))
			bnx2x__common_init_phy(bp);
	} else
		BNX2X_ERR("Bootcode is missing - can not initialize link\n");

	if (SHMEM2_HAS(bp, netproc_fw_ver))
		SHMEM2_WR(bp, netproc_fw_ver, REG_RD(bp, XSEM_REG_PRAM));

	return 0;
}
