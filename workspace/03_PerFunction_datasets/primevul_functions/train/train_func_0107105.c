static void sdhci_set_readonly(DeviceState *dev, bool level)
{
    SDHCIState *s = (SDHCIState *)dev;

    if (level) {
        s->prnsts &= ~SDHC_WRITE_PROTECT;
    } else {

        s->prnsts |= SDHC_WRITE_PROTECT;
    }
}
