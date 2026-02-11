manageApp(App *app, int flags)
{
    if (flags & MPR_MANAGE_MARK) {
        mprMark(app);
    }
}
