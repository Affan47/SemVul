set_global_step(void)
{
    global_step = local_step = POPn;
    if (global_step <= 0) runtime_error(_("invalid size"));
}
