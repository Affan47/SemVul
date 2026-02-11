ql_get_mpi_shadow_regs(struct ql_adapter *qdev, u32 *buf)
{
	u32 i;
	int status;

	for (i = 0; i < MPI_CORE_SH_REGS_CNT; i++, buf++) {
		status = ql_write_mpi_reg(qdev, RISC_124,
				(SHADOW_OFFSET | i << SHADOW_REG_SHIFT));
		if (status)
			goto end;
		status = ql_read_mpi_reg(qdev, RISC_127, buf);
		if (status)
			goto end;
	}
end:
	return status;
}
