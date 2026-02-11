_intr_mode_str(void *isr)
{
    int imx;

    imx = 0;
    while (_intr_mode[imx].isr != NULL) {
        if (isr == _intr_mode[imx].isr) {
            return _intr_mode[imx].name;
        }
        imx++;
    }
    return NULL;
}
