static void fdctrl_handle_version(FDCtrl *fdctrl, int direction)
{

    fdctrl->fifo[0] = fdctrl->version;
    fdctrl_to_result_phase(fdctrl, 1);
}
