int main(int argc, char *argv[])
{
    g_test_init(&argc, &argv, NULL);


    g_test_add_func("/server/memslot-invalid-addresses", test_memslot_invalid_addresses);
    g_test_add_func("/server/memslot-invalid-addresses/subprocess/group_id", test_memslot_invalid_group_id);
    g_test_add_func("/server/memslot-invalid-addresses/subprocess/slot_id", test_memslot_invalid_slot_id);


    g_test_add_func("/server/qxl-parsing-no-issues", test_no_issues);


    g_test_add_func("/server/qxl-parsing/stride-too-small", test_stride_too_small);


    g_test_add_func("/server/qxl-parsing/too-big-image", test_too_big_image);


    g_test_add_func("/server/qxl-parsing/base-cursor-command", test_cursor_command);


    g_test_add_func("/server/qxl-parsing/circular-empty-chunks", test_circular_empty_chunks);


    g_test_add_func("/server/qxl-parsing/circular-small-chunks", test_circular_small_chunks);

    return g_test_run();
}
