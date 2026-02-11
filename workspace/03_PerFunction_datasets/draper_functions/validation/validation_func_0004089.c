set_global_size(_param p)
{
    global_size = local_size = p.num;
    if (global_size <= 0) runtime_error(_("invalid size"));
}
