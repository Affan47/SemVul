usdhc_write(void *opaque, hwaddr offset, uint64_t val, unsigned size)
{
    SDHCIState *s = SYSBUS_SDHCI(opaque);
    uint8_t hostctl1;
    uint32_t value = (uint32_t)val;

    switch (offset) {
    case ESDHC_DLL_CTRL:
    case ESDHC_TUNE_CTRL_STATUS:
    case ESDHC_UNDOCUMENTED_REG27:
    case ESDHC_TUNING_CTRL:
    case ESDHC_WTMK_LVL:
        break;

    case ESDHC_VENDOR_SPEC:
        s->vendor_spec = value;
        switch (s->vendor) {
        case SDHCI_VENDOR_IMX:
            if (value & ESDHC_IMX_FRC_SDCLK_ON) {
                s->prnsts &= ~SDHC_IMX_CLOCK_GATE_OFF;
            } else {
                s->prnsts |= SDHC_IMX_CLOCK_GATE_OFF;
            }
            break;
        default:
            break;
        }
        break;

    case SDHC_HOSTCTL:


        hostctl1 = value & (SDHC_CTRL_LED |
                            SDHC_CTRL_CDTEST_INS |
                            SDHC_CTRL_CDTEST_EN);


        if (value & ESDHC_CTRL_8BITBUS) {
            hostctl1 |= SDHC_CTRL_8BITBUS;
        }

        if (value & ESDHC_CTRL_4BITBUS) {
            hostctl1 |= ESDHC_CTRL_4BITBUS;
        }


        hostctl1 |= SDHC_DMA_TYPE(value >> (8 - 3));


        value &= ~UINT16_MAX;
        value |= hostctl1;
        value |= (uint16_t)s->pwrcon << 8;

        sdhci_write(opaque, offset, value, size);
        break;

    case ESDHC_MIX_CTRL:


        s->trnmod = value & UINT16_MAX;
        break;
    case SDHC_TRNMOD:


        sdhci_write(opaque, offset, val | s->trnmod, size);
        break;
    case SDHC_BLKSIZE:


        val |= 0x7 << 12;

    default:
        sdhci_write(opaque, offset, val, size);
        break;
    }
}
