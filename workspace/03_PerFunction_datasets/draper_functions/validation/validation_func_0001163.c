HxDoHexOutput (
    void)
{

    switch (Gbl_HexOutputFlag)
    {
    case HEX_OUTPUT_C:

        HxDoHexOutputC ();
        break;

    case HEX_OUTPUT_ASM:

        HxDoHexOutputAsm ();
        break;

    case HEX_OUTPUT_ASL:

        HxDoHexOutputAsl ();
        break;

    default:


        break;
    }
}
