void page_size_init(struct uc_struct *uc)
{


    if (uc->qemu_host_page_size == 0) {
        uc->qemu_host_page_size = uc->qemu_real_host_page_size;
    }
    if (uc->qemu_host_page_size < TARGET_PAGE_SIZE) {
        uc->qemu_host_page_size = TARGET_PAGE_SIZE;
    }
}
