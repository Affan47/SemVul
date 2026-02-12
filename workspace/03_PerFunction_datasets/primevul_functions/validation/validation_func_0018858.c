ip_invoke_core(interp, argc, argv)
    VALUE interp;
    int argc;
    char **argv;
#endif
{
    struct tcltkip *ptr;
    Tcl_CmdInfo info;
    char *cmd;
    int  len;
    int  thr_crit_bup;
    int unknown_flag = 0;

#if 1
    struct invoke_info inf;
    int status;
#else
#if TCL_MAJOR_VERSION >= 8
    int argc = objc;
    char **argv = (char **)NULL;

#endif
#endif


#if TCL_MAJOR_VERSION >= 8
    cmd = Tcl_GetStringFromObj(objv[0], &len);
#else
    cmd = argv[0];
#endif


    ptr = get_ip(interp);


    if (deleted_ip(ptr)) {
        return rb_tainted_str_new2("");
    }


    rbtk_preserve_ip(ptr);


    DUMP2("call Tcl_GetCommandInfo, %s", cmd);
    if (!Tcl_GetCommandInfo(ptr->ip, cmd, &info)) {
        DUMP1("error Tcl_GetCommandInfo");
        DUMP1("try auto_load (call 'unknown' command)");
        if (!Tcl_GetCommandInfo(ptr->ip,
#if TCL_MAJOR_VERSION >= 8
                                "::unknown",
#else
                                "unknown",
#endif
                                &info)) {
            DUMP1("fail to get 'unknown' command");

            if (event_loop_abort_on_exc > 0) {

                rbtk_release_ip(ptr);

                return create_ip_exc(interp, rb_eNameError,
                                     "invalid command name `%s'", cmd);
            } else {
                if (event_loop_abort_on_exc < 0) {
                    rb_warning("invalid command name `%s' (ignore)", cmd);
                } else {
                    rb_warn("invalid command name `%s' (ignore)", cmd);
                }
                Tcl_ResetResult(ptr->ip);

                rbtk_release_ip(ptr);
                return rb_tainted_str_new2("");
            }
        } else {
#if TCL_MAJOR_VERSION >= 8
            Tcl_Obj **unknown_objv;
#else
            char **unknown_argv;
#endif
            DUMP1("find 'unknown' command -> set arguemnts");
            unknown_flag = 1;

#if TCL_MAJOR_VERSION >= 8

            unknown_objv = RbTk_ALLOC_N(Tcl_Obj *, (objc+2));
#if 0
	    Tcl_Preserve((ClientData)unknown_objv);
#endif
            unknown_objv[0] = Tcl_NewStringObj("::unknown", 9);
            Tcl_IncrRefCount(unknown_objv[0]);
            memcpy(unknown_objv + 1, objv, sizeof(Tcl_Obj *)*objc);
            unknown_objv[++objc] = (Tcl_Obj*)NULL;
            objv = unknown_objv;
#else

            unknown_argv = RbTk_ALLOC_N(char *, (argc+2));
#if 0
	    Tcl_Preserve((ClientData)unknown_argv);
#endif
            unknown_argv[0] = strdup("unknown");
            memcpy(unknown_argv + 1, argv, sizeof(char *)*argc);
            unknown_argv[++argc] = (char *)NULL;
            argv = unknown_argv;
#endif
        }
    }
    DUMP1("end Tcl_GetCommandInfo");

    thr_crit_bup = rb_thread_critical;
    rb_thread_critical = Qtrue;

#if 1

    inf.ptr = ptr;
    inf.cmdinfo = info;
#if TCL_MAJOR_VERSION >= 8
    inf.objc = objc;
    inf.objv = objv;
#else
    inf.argc = argc;
    inf.argv = argv;
#endif


    DUMP1("invoke tcl-proc");
    rb_protect(invoke_tcl_proc, (VALUE)&inf, &status);
    DUMP2("status of tcl-proc, %d", status);
    switch(status) {
    case TAG_RAISE:
        if (NIL_P(rb_errinfo())) {
            rbtk_pending_exception = rb_exc_new2(rb_eException,
                                                 "unknown exception");
        } else {
            rbtk_pending_exception = rb_errinfo();
        }
        break;

    case TAG_FATAL:
        if (NIL_P(rb_errinfo())) {
            rbtk_pending_exception = rb_exc_new2(rb_eFatal, "FATAL");
        } else {
            rbtk_pending_exception = rb_errinfo();
        }
    }

#else


#if TCL_MAJOR_VERSION >= 8
    if (!info.isNativeObjectProc) {
        int i;


        argv = RbTk_ALLOC_N(char *, (argc+1));
#if 0
	Tcl_Preserve((ClientData)argv);
#endif
        for (i = 0; i < argc; ++i) {
            argv[i] = Tcl_GetStringFromObj(objv[i], &len);
        }
        argv[argc] = (char *)NULL;
    }
#endif

    Tcl_ResetResult(ptr->ip);


#if TCL_MAJOR_VERSION >= 8
    if (info.isNativeObjectProc) {
        ptr->return_value = (*info.objProc)(info.objClientData, ptr->ip,
                                            objc, objv);
#if 0

        resultPtr = Tcl_GetObjResult(ptr->ip);
        Tcl_SetResult(ptr->ip, Tcl_GetStringFromObj(resultPtr, &len),
                      TCL_VOLATILE);
#endif
    }
    else
#endif
    {
#if TCL_MAJOR_VERSION >= 8
        ptr->return_value = (*info.proc)(info.clientData, ptr->ip,
                                         argc, (CONST84 char **)argv);

#if 0
    Tcl_EventuallyFree((ClientData)argv, TCL_DYNAMIC);
#else
#if 0
	Tcl_Release((ClientData)argv);
#else

        ckfree((char*)argv);
#endif
#endif

#else
        ptr->return_value = (*info.proc)(info.clientData, ptr->ip,
                                         argc, argv);
#endif
    }
#endif


    if (unknown_flag) {
#if TCL_MAJOR_VERSION >= 8
        Tcl_DecrRefCount(objv[0]);
#if 0
	Tcl_EventuallyFree((ClientData)objv, TCL_DYNAMIC);
#else
#if 0
	Tcl_Release((ClientData)objv);
#else

        ckfree((char*)objv);
#endif
#endif
#else
        free(argv[0]);

#if 0
	Tcl_EventuallyFree((ClientData)argv, TCL_DYNAMIC);
#else
#if 0
	Tcl_Release((ClientData)argv);
#else

        ckfree((char*)argv);
#endif
#endif
#endif
    }


    if (pending_exception_check1(thr_crit_bup, ptr)) {
        return rbtk_pending_exception;
    }

    rb_thread_critical = thr_crit_bup;


    if (ptr->return_value != TCL_OK) {
        if (event_loop_abort_on_exc > 0 && !Tcl_InterpDeleted(ptr->ip)) {
	    switch (ptr->return_value) {
	    case TCL_RETURN:
	      return create_ip_exc(interp, eTkCallbackReturn,
				   "ip_invoke_core receives TCL_RETURN");
	    case TCL_BREAK:
	      return create_ip_exc(interp, eTkCallbackBreak,
				   "ip_invoke_core receives TCL_BREAK");
	    case TCL_CONTINUE:
	      return create_ip_exc(interp, eTkCallbackContinue,
				   "ip_invoke_core receives TCL_CONTINUE");
	    default:
	      return create_ip_exc(interp, rb_eRuntimeError, "%s",
				   Tcl_GetStringResult(ptr->ip));
	    }

        } else {
            if (event_loop_abort_on_exc < 0) {
                rb_warning("%s (ignore)", Tcl_GetStringResult(ptr->ip));
            } else {
                rb_warn("%s (ignore)", Tcl_GetStringResult(ptr->ip));
            }
            Tcl_ResetResult(ptr->ip);
            return rb_tainted_str_new2("");
        }
    }


    return ip_get_result_string_obj(ptr->ip);
}
