AcpiTbInstallTableWithOverride (
    UINT32                  TableIndex,
    ACPI_TABLE_DESC         *NewTableDesc,
    BOOLEAN                 Override)
{

    if (TableIndex >= AcpiGbl_RootTableList.CurrentTableCount)
    {
        return;
    }


    if (Override)
    {
        AcpiTbOverrideTable (NewTableDesc);
    }

    AcpiTbInitTableDescriptor (&AcpiGbl_RootTableList.Tables[TableIndex],
        NewTableDesc->Address, NewTableDesc->Flags, NewTableDesc->Pointer);

    AcpiTbPrintTableHeader (NewTableDesc->Address, NewTableDesc->Pointer);


    if (TableIndex == ACPI_TABLE_INDEX_DSDT)
    {
        AcpiUtSetIntegerWidth (NewTableDesc->Pointer->Revision);
    }
}
