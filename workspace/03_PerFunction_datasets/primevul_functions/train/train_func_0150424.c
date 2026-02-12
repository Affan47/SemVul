JVM_ActiveProcessorCount(void)
{
	PORT_ACCESS_FROM_JAVAVM(BFUjavaVM);
	jint num;

	Trc_SC_ActiveProcessorCount_Entry();


	num = (jint)j9sysinfo_get_number_CPUs_by_type(J9PORT_CPU_TARGET);
	if (num < 1) {
		num = 1;
	}

	Trc_SC_ActiveProcessorCount_Exit(num);

	return num;
}
