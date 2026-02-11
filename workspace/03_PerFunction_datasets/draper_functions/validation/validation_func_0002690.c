OpnDoPackage (
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_PARSE_OBJECT       *InitializerOp;
    ACPI_PARSE_OBJECT       *PackageLengthOp;
    UINT32                  PackageLength = 0;


    PackageLengthOp = Op->Asl.Child;
    InitializerOp = PackageLengthOp->Asl.Next;


    if (InitializerOp->Asl.ParseOpcode != PARSEOP_DEFAULT_ARG)
    {


        while (InitializerOp)
        {
            PackageLength++;
            InitializerOp = InitializerOp->Asl.Next;
        }
    }


    if ((PackageLengthOp->Asl.ParseOpcode == PARSEOP_INTEGER)      ||
        (PackageLengthOp->Asl.ParseOpcode == PARSEOP_QWORDCONST))
    {
        if (PackageLengthOp->Asl.Value.Integer > PackageLength)
        {


            if (PackageLength > 0)
            {
                AslError (ASL_REMARK, ASL_MSG_LIST_LENGTH_SHORT,
                    PackageLengthOp, NULL);
            }

            PackageLength = (UINT32) PackageLengthOp->Asl.Value.Integer;
        }
        else if (PackageLengthOp->Asl.Value.Integer < PackageLength)
        {


            AslError (ASL_ERROR, ASL_MSG_LIST_LENGTH_LONG,
                PackageLengthOp, NULL);
        }
    }

    if (PackageLengthOp->Asl.ParseOpcode == PARSEOP_DEFAULT_ARG)
    {


        Op->Asl.Child->Asl.ParseOpcode = PARSEOP_INTEGER;
        Op->Asl.Child->Asl.Value.Integer = PackageLength;


        (void) OpcSetOptimalIntegerSize (Op->Asl.Child);
    }


    if ((PackageLengthOp->Asl.ParseOpcode == PARSEOP_INTEGER)      ||
        (PackageLengthOp->Asl.ParseOpcode == PARSEOP_QWORDCONST)   ||
        (PackageLengthOp->Asl.ParseOpcode == PARSEOP_ZERO)         ||
        (PackageLengthOp->Asl.ParseOpcode == PARSEOP_DEFAULT_ARG))
    {
        if (!PackageLength)
        {


            AslError (ASL_REMARK, ASL_MSG_PACKAGE_LENGTH,
                PackageLengthOp, NULL);


        }
    }


    if (((Op->Asl.Child->Asl.ParseOpcode == PARSEOP_INTEGER) &&
            (Op->Asl.Child->Asl.Value.Integer <= 255))  ||
        (Op->Asl.Child->Asl.ParseOpcode == PARSEOP_ONE) ||
        (Op->Asl.Child->Asl.ParseOpcode == PARSEOP_ONES)||
        (Op->Asl.Child->Asl.ParseOpcode == PARSEOP_ZERO))
    {
        Op->Asl.AmlOpcode = AML_PACKAGE_OP;
        Op->Asl.ParseOpcode = PARSEOP_PACKAGE;


        PackageLengthOp->Asl.AmlOpcode = AML_RAW_DATA_BYTE;
        PackageLengthOp->Asl.AmlLength = 1;
        PackageLengthOp->Asl.ParseOpcode = PARSEOP_RAW_DATA;
        PackageLengthOp->Asl.Value.Integer = PackageLength;
    }


}
