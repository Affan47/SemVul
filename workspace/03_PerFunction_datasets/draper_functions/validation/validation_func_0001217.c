AcpiPsHasCompletedScope (
    ACPI_PARSE_STATE        *ParserState)
{

    return ((BOOLEAN)
            ((ParserState->Aml >= ParserState->Scope->ParseScope.ArgEnd ||
             !ParserState->Scope->ParseScope.ArgCount)));
}
