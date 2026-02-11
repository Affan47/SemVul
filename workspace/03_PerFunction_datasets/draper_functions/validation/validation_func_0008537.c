to_external(internal)
short int internal;
{
    short int  external;

    if (internal & BIT(IPX_NONE) )
        external = IPX_NONE;
    else
        external = RIP_SAP;

    return external;
}
