locate_subdirs(std::string directory, std::vector<std::string>& result)
{
    CYG_REPORT_FUNCNAME("CdlInterpreter::locate_subdirs");
    CYG_REPORT_FUNCARG2XV(this, &result);
    CYG_PRECONDITION_THISC();

    static char locate_subdirs_script[] = "\
set pattern [file join \"$::cdl_locate_subdirs_path\" * .]  \n\
set result {}                                               \n\
foreach entry [glob -nocomplain -- $pattern] {              \n\
    set entry [file tail [file dirname $entry]]             \n\
    if {($entry != \"CVS\") && ($entry != \"cvs\")} {       \n\
        lappend result $entry                               \n\
    }                                                       \n\
}                                                           \n\
return $result                                              \n\
";

    std::string                 tcl_result = "";
    set_variable("::cdl_locate_subdirs_path", directory);
    if (TCL_OK != eval(locate_subdirs_script, tcl_result)) {
        CYG_FAIL("Internal error evaluating Tcl script");
    }

    int             count;
    const char**    array;
    if (TCL_OK != Tcl_SplitList(tcl_interp, CDL_TCL_CONST_CAST(char*, tcl_result.c_str()), &count, CDL_TCL_CONST_CAST(char***, &array))) {
        throw std::bad_alloc();
    }
    for (int i = 0; i < count; i++) {
        result.push_back(array[i]);
    }
    Tcl_Free((char*) array);

    CYG_REPORT_RETURN();
}
