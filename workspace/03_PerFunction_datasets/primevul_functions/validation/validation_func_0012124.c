static void sm501_reset_pci(DeviceState *dev)
{
    SM501PCIState *s = PCI_SM501(dev);
    sm501_reset(&s->state);

    s->state.misc_control |= 1;
}
