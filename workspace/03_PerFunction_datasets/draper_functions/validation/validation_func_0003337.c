tcl_command_proc(ClientData data, Tcl_Interp* tcl_interp, int argc, const char* argv[])
{
    CYG_REPORT_FUNCNAMETYPE("CdlInterpreter::tcl_command_proc", "result %d");
    CYG_REPORT_FUNCARG3XV(data, tcl_interp, argc);
    CYG_PRECONDITIONC(0 != data);

    int result = TCL_OK;

    union {
        ClientData            data;
        CdlInterpreterCommand command;
    } x;
    x.data = data;
    CdlInterpreterCommand command = x.command;

    data = Tcl_GetAssocData(tcl_interp, cdlinterpreter_assoc_data_key, 0);
    CdlInterpreter interp = static_cast<CdlInterpreter>(data);
    CYG_ASSERT_CLASSC(interp);

    try {
        result = (*command)(interp, argc, argv);
    } catch(std::bad_alloc e) {
        interp->set_result(CdlParse::construct_diagnostic(interp, "internal error", "", "Out of memory."));
        result = TCL_ERROR;
    } catch(CdlStringException e) {
        interp->set_result(e.get_message());
        result = TCL_ERROR;
    } catch(...) {
        CYG_FAIL("Unexpected C++ exception");
        interp->set_result(CdlParse::construct_diagnostic(interp, "internal error", "", "Unexpected C++ exception."));
        result = TCL_ERROR;
    }

    CYG_REPORT_RETVAL(result);
    return result;
}
