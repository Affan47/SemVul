sparse_init(void)
{
	unsigned long pnum;
	struct page *map;
	unsigned long *usemap;
	unsigned long **usemap_map;
	int size;
#ifdef CONFIG_SPARSEMEM_ALLOC_MEM_MAP_TOGETHER
	int size2;
	struct page **map_map;
#endif


	BUILD_BUG_ON(!is_power_of_2(sizeof(struct mem_section)));


	set_pageblock_order();


	size = sizeof(unsigned long *) * NR_MEM_SECTIONS;
	usemap_map = memblock_virt_alloc(size, 0);
	if (!usemap_map)
		panic("can not allocate usemap_map\n");
	alloc_usemap_and_memmap(sparse_early_usemaps_alloc_node,
							(void *)usemap_map);

#ifdef CONFIG_SPARSEMEM_ALLOC_MEM_MAP_TOGETHER
	size2 = sizeof(struct page *) * NR_MEM_SECTIONS;
	map_map = memblock_virt_alloc(size2, 0);
	if (!map_map)
		panic("can not allocate map_map\n");
	alloc_usemap_and_memmap(sparse_early_mem_maps_alloc_node,
							(void *)map_map);
#endif

	for (pnum = 0; pnum < NR_MEM_SECTIONS; pnum++) {
		if (!present_section_nr(pnum))
			continue;

		usemap = usemap_map[pnum];
		if (!usemap)
			continue;

#ifdef CONFIG_SPARSEMEM_ALLOC_MEM_MAP_TOGETHER
		map = map_map[pnum];
#else
		map = sparse_early_mem_map_alloc(pnum);
#endif
		if (!map)
			continue;

		sparse_init_one_section(__nr_to_section(pnum), pnum, map,
								usemap);
	}

	vmemmap_populate_print_last();

#ifdef CONFIG_SPARSEMEM_ALLOC_MEM_MAP_TOGETHER
	memblock_free_early(__pa(map_map), size2);
#endif
	memblock_free_early(__pa(usemap_map), size);
}
