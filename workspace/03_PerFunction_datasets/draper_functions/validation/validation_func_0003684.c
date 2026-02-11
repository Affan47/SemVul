parse_if_define_final_check(CdlInterpreter interp, CdlProperty_StringVector prop)
{
    CYG_REPORT_FUNCNAME("parse_if_define_final_check");
    CYG_PRECONDITION_CLASSC(interp);
    CYG_PRECONDITION_CLASSC(prop);


    const std::vector<std::string>& strings     = prop->get_strings();

    if (2 != strings.size()) {
        CdlParse::report_property_parse_error(interp, prop, "There should be exactly two arguments.");
    }
    if (!Cdl::is_valid_c_preprocessor_symbol(strings[0])) {
        CdlParse::report_property_parse_error(interp, prop, strings[0] + " is not a valid C preprocessor symbol.");
    }
    if (!Cdl::is_valid_c_preprocessor_symbol(strings[1])) {
        CdlParse::report_property_parse_error(interp, prop, strings[1] + " is not a valid C preprocessor symbol.");
    }


    std::string file_option = prop->get_option("file");
    if (("" != file_option) && ("system.h" != file_option)) {
        CdlParse::report_property_parse_error(interp, prop, "Invalid -file option " + file_option);
    }
}
