static void fdctrl_handle_partid(FDCtrl *fdctrl, int direction)
{
    fdctrl->fifo[0] = 0x41;
    fdctrl_to_result_phase(fdctrl, 1);
}
