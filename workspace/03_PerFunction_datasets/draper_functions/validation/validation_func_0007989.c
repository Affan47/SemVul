AcpiUtGetPackageObjectSize (
    ACPI_OPERAND_OBJECT     *InternalObject,
    ACPI_SIZE               *ObjLength)
{
    ACPI_STATUS             Status;
    ACPI_PKG_INFO           Info;


    ACPI_FUNCTION_TRACE_PTR (UtGetPackageObjectSize, InternalObject);


    Info.Length      = 0;
    Info.ObjectSpace = 0;
    Info.NumPackages = 1;

    Status = AcpiUtWalkPackageTree (InternalObject, NULL,
        AcpiUtGetElementLength, &Info);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }


    Info.Length += ACPI_ROUND_UP_TO_NATIVE_WORD (sizeof (ACPI_OBJECT)) *
                    (ACPI_SIZE) Info.NumPackages;


    *ObjLength = Info.Length;
    return_ACPI_STATUS (Status);
}
