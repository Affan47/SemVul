AcpiDmDumpDataTable (
    ACPI_TABLE_HEADER       *Table)
{
    ACPI_STATUS             Status;
    ACPI_DMTABLE_DATA       *TableData;
    UINT32                  Length;


    if (AcpiUtIsAmlTable (Table))
    {
        if (Gbl_VerboseTemplates)
        {


            Length = Table->Length;

            AcpiOsPrintf ("\n/*\n%s: Length %d (0x%X)\n\n",
                ACPI_RAW_TABLE_DATA_HEADER, Length, Length);
            AcpiUtDumpBuffer (ACPI_CAST_PTR (UINT8, Table),
                Length, DB_BYTE_DISPLAY, 0);
            AcpiOsPrintf (" */\n");
        }
        return;
    }


    if (ACPI_COMPARE_NAME (Table->Signature, ACPI_SIG_FACS))
    {
        Length = Table->Length;
        AcpiDmDumpTable (Length, 0, Table, 0, AcpiDmTableInfoFacs);
    }
    else if (ACPI_VALIDATE_RSDP_SIG (Table->Signature))
    {
        Length = AcpiDmDumpRsdp (Table);
    }
    else if (ACPI_COMPARE_NAME (Table->Signature, ACPI_SIG_S3PT))
    {
        Length = AcpiDmDumpS3pt (Table);
    }
    else
    {


        Length = Table->Length;
        Status = AcpiDmDumpTable (Length, 0, Table, 0, AcpiDmTableInfoHeader);
        if (ACPI_FAILURE (Status))
        {
            return;
        }
        AcpiOsPrintf ("\n");


        TableData = AcpiDmGetTableData (Table->Signature);
        if (!TableData)
        {
            if (!ACPI_STRNCMP (Table->Signature, "OEM", 3))
            {
                AcpiOsPrintf ("\n**** OEM-defined ACPI table [%4.4s], unknown contents\n\n",
                    Table->Signature);
            }
            else
            {
                AcpiOsPrintf ("\n**** Unknown ACPI table type [%4.4s]\n\n",
                    Table->Signature);
                fprintf (stderr, "Unknown ACPI table signature [%4.4s], decoding header only\n",
                    Table->Signature);
            }
        }
        else if (TableData->TableHandler)
        {


            TableData->TableHandler (Table);
        }
        else if (TableData->TableInfo)
        {


            AcpiDmDumpTable (Length, 0, Table, 0, TableData->TableInfo);
        }
    }

    if (!Gbl_DoTemplates || Gbl_VerboseTemplates)
    {


        AcpiOsPrintf ("\n%s: Length %d (0x%X)\n\n",
            ACPI_RAW_TABLE_DATA_HEADER, Length, Length);
        AcpiUtDumpBuffer (ACPI_CAST_PTR (UINT8, Table),
            Length, DB_BYTE_DISPLAY, 0);
    }
}
