static uint16_t phys_section_add(struct uc_struct *uc, PhysPageMap *map,
                                 MemoryRegionSection *section)
{


    assert(map->sections_nb < TARGET_PAGE_SIZE);

    if (map->sections_nb == map->sections_nb_alloc) {
        map->sections_nb_alloc = MAX(map->sections_nb_alloc * 2, 16);
        map->sections = g_renew(MemoryRegionSection, map->sections,
                                map->sections_nb_alloc);
    }
    map->sections[map->sections_nb] = *section;
    return map->sections_nb++;
}
