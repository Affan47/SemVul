static void test_too_big_image(void)
{
    RedMemSlotInfo mem_info;
    RedSurfaceCmd *cmd;
    QXLSurfaceCmd qxl;

    init_meminfo(&mem_info);
    init_qxl_surface(&qxl);


    qxl.u.surface_create.stride = 0x08000004 * 4;
    qxl.u.surface_create.width = 0x08000004;
    qxl.u.surface_create.height = 0x40000020;
    cmd = red_surface_cmd_new(NULL, &mem_info, 0, to_physical(&qxl));
    g_assert_null(cmd);

    deinit_qxl_surface(&qxl);
    memslot_info_destroy(&mem_info);
}
