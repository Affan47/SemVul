checkDisplay(string &as)
{
    int retval = 0;

    semaphore_down(&access_imgvect);
    if (!imgToDisplay.empty()) {
        as = imgToDisplay.front();
        dbgprintf("Aha: image %s is to be displayed!\n", as.c_str());

        imgToDisplay.erase(imgToDisplay.begin());
        retval = 1;
    }
    semaphore_up(&access_imgvect);

    return retval;
}
