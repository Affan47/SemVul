CheckInit (
    StructInitInfo *    module )
{
    Int                 success = 1;

    if ( NCopyAndFopyGVars != NCopyAndFopyDone ) {
        success = 0;
        Pr( "#W  failed to updated copies and fopies\n", 0L, 0L );
    }


    return ! success;
}
