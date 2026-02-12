static void phys_section_destroy(MemoryRegion *mr)
{
    bool have_sub_page = mr->subpage;

    if (have_sub_page) {
        subpage_t *subpage = container_of(mr, subpage_t, iomem);

        g_free(subpage);
    }
}
