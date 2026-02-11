AcpiPsExecuteMethod (
    ACPI_EVALUATE_INFO      *Info)
{
    ACPI_STATUS             Status;
    ACPI_PARSE_OBJECT       *Op;
    ACPI_WALK_STATE         *WalkState;


    ACPI_FUNCTION_TRACE (PsExecuteMethod);


    AcpiTbCheckDsdtHeader ();


    if (!Info || !Info->Node)
    {
        return_ACPI_STATUS (AE_NULL_ENTRY);
    }


    Status = AcpiDsBeginMethodExecution (Info->Node, Info->ObjDesc, NULL);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }


    AcpiPsUpdateParameterList (Info, REF_INCREMENT);


    AcpiPsStartTrace (Info);


    ACPI_DEBUG_PRINT ((ACPI_DB_PARSE,
        "**** Begin Method Parse/Execute [%4.4s] **** Node=%p Obj=%p\n",
        Info->Node->Name.Ascii, Info->Node, Info->ObjDesc));


    Op = AcpiPsCreateScopeOp ();
    if (!Op)
    {
        Status = AE_NO_MEMORY;
        goto Cleanup;
    }


    Info->PassNumber = ACPI_IMODE_EXECUTE;
    WalkState = AcpiDsCreateWalkState (
                    Info->ObjDesc->Method.OwnerId, NULL, NULL, NULL);
    if (!WalkState)
    {
        Status = AE_NO_MEMORY;
        goto Cleanup;
    }

    Status = AcpiDsInitAmlWalk (WalkState, Op, Info->Node,
                Info->ObjDesc->Method.AmlStart,
                Info->ObjDesc->Method.AmlLength, Info, Info->PassNumber);
    if (ACPI_FAILURE (Status))
    {
        AcpiDsDeleteWalkState (WalkState);
        goto Cleanup;
    }

    if (Info->ObjDesc->Method.InfoFlags & ACPI_METHOD_MODULE_LEVEL)
    {
        WalkState->ParseFlags |= ACPI_PARSE_MODULE_LEVEL;
    }


    if (Info->ObjDesc->Method.InfoFlags & ACPI_METHOD_INTERNAL_ONLY)
    {
        Status = Info->ObjDesc->Method.Dispatch.Implementation (WalkState);
        Info->ReturnObject = WalkState->ReturnDesc;


        AcpiDsScopeStackClear (WalkState);
        AcpiPsCleanupScope (&WalkState->ParserState);
        AcpiDsTerminateControlMethod (WalkState->MethodDesc, WalkState);
        AcpiDsDeleteWalkState (WalkState);
        goto Cleanup;
    }


    if (AcpiGbl_EnableInterpreterSlack)
    {
        WalkState->ImplicitReturnObj =
            AcpiUtCreateIntegerObject ((UINT64) 0);
        if (!WalkState->ImplicitReturnObj)
        {
            Status = AE_NO_MEMORY;
            AcpiDsDeleteWalkState (WalkState);
            goto Cleanup;
        }
    }


    Status = AcpiPsParseAml (WalkState);


Cleanup:
    AcpiPsDeleteParseTree (Op);


    AcpiPsStopTrace (Info);


    AcpiPsUpdateParameterList (Info, REF_DECREMENT);


    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }


    if (Info->ReturnObject)
    {
        ACPI_DEBUG_PRINT ((ACPI_DB_PARSE, "Method returned ObjDesc=%p\n",
            Info->ReturnObject));
        ACPI_DUMP_STACK_ENTRY (Info->ReturnObject);

        Status = AE_CTRL_RETURN_VALUE;
    }

    return_ACPI_STATUS (Status);
}
