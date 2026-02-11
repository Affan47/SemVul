DI_timer(AW_root *aw_root, AW_CL cl_gbmain, AW_CL cd2) {
    GBDATA *gb_main = reinterpret_cast<GBDATA*>(cl_gbmain);
    {
        GB_transaction ta(gb_main);
        GB_tell_server_dont_wait(gb_main);
    }
    aw_root->add_timed_callback(500, DI_timer, cl_gbmain, cd2);
}
