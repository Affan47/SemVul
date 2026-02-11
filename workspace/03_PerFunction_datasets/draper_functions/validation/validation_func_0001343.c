removeLine(void)
{
    keepProfileLine = false;
    if (angleLine != 0) {

    parentWindow->make_current();
    angleLine->undraw();
    remove(angleLine);
    delete angleLine;
    angleLine = 0;
    }
    return;
}
