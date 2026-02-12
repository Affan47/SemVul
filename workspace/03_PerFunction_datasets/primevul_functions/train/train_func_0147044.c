static void __build_all_zonelists(void *data)
{
	int nid;
	int __maybe_unused cpu;
	pg_data_t *self = data;
	static DEFINE_SPINLOCK(lock);

	spin_lock(&lock);

#ifdef CONFIG_NUMA
	memset(node_load, 0, sizeof(node_load));
#endif


	if (self && !node_online(self->node_id)) {
		build_zonelists(self);
	} else {
		for_each_online_node(nid) {
			pg_data_t *pgdat = NODE_DATA(nid);

			build_zonelists(pgdat);
		}

#ifdef CONFIG_HAVE_MEMORYLESS_NODES


		for_each_online_cpu(cpu)
			set_cpu_numa_mem(cpu, local_memory_node(cpu_to_node(cpu)));
#endif
	}

	spin_unlock(&lock);
}
