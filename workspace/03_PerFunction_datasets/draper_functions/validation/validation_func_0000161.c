SCPI_ParamChoice(scpi_t * context, const scpi_choice_def_t * options, int32_t * value, scpi_bool_t mandatory) {
    scpi_bool_t result;
    scpi_parameter_t param;

    if (!options || !value) {
        SCPI_ErrorPush(context, SCPI_ERROR_SYSTEM_ERROR);
        return FALSE;
    }

    result = SCPI_Parameter(context, &param, mandatory);
    if (result) {
        result = SCPI_ParamToChoice(context, &param, options, value);
    }

    return result;
}
