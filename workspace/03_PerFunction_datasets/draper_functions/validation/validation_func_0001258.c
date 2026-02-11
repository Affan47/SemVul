gdth_test_busy(gdth_ha_str *ha)
{
    register int gdtsema0 = 0;

    TRACE(("gdth_test_busy() hanum %d\n", ha->hanum));

    if (ha->type == GDT_EISA)
        gdtsema0 = (int)inb(ha->bmic + SEMA0REG);
    else if (ha->type == GDT_ISA)
        gdtsema0 = (int)readb(&((gdt2_dpram_str __iomem *)ha->brd)->u.ic.Sema0);
    else if (ha->type == GDT_PCI)
        gdtsema0 = (int)readb(&((gdt6_dpram_str __iomem *)ha->brd)->u.ic.Sema0);
    else if (ha->type == GDT_PCINEW)
        gdtsema0 = (int)inb(PTR2USHORT(&ha->plx->sema0_reg));
    else if (ha->type == GDT_PCIMPR)
        gdtsema0 =
            (int)readb(&((gdt6m_dpram_str __iomem *)ha->brd)->i960r.sema0_reg);

    return (gdtsema0 & 1);
}
