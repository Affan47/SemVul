AcpiNsRepair_TSS (
    ACPI_EVALUATE_INFO      *Info,
    ACPI_OPERAND_OBJECT     **ReturnObjectPtr)
{
    ACPI_OPERAND_OBJECT     *ReturnObject = *ReturnObjectPtr;
    ACPI_STATUS             Status;
    ACPI_NAMESPACE_NODE     *Node;


    Status = AcpiNsGetNode (Info->Node, "^_PSS",
        ACPI_NS_NO_UPSEARCH, &Node);
    if (ACPI_SUCCESS (Status))
    {
        return (AE_OK);
    }

    Status = AcpiNsCheckSortedList (Info, ReturnObject, 0, 5, 1,
                ACPI_SORT_DESCENDING, "PowerDissipation");

    return (Status);
}
