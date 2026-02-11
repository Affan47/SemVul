internal_dasm(int cpunum, char *buffer, unsigned pc)
{
	unsigned result;
	if (cpu_dasm_override)
	{
		result = cpu_dasm_override(cpunum, buffer, pc);
		if (result)
			return result;
	}
	return (*cpu[cpunum].intf.cpu_dasm)(buffer, pc);
}
