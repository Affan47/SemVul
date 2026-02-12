ip_invoke_with_position(argc, argv, obj, position)
    int argc;
    VALUE *argv;
    VALUE obj;
    Tcl_QueuePosition position;
{
    struct invoke_queue *ivq;
#ifdef RUBY_USE_NATIVE_THREAD
    struct tcltkip *ptr;
#endif
    int  *alloc_done;
    int  thr_crit_bup;
    volatile VALUE current = rb_thread_current();
    volatile VALUE ip_obj = obj;
    volatile VALUE result;
    volatile VALUE ret;
    struct timeval t;

#if TCL_MAJOR_VERSION >= 8
    Tcl_Obj **av = (Tcl_Obj **)NULL;
#else
    char **av = (char **)NULL;
#endif

    if (argc < 1) {
        rb_raise(rb_eArgError, "command name missing");
    }

#ifdef RUBY_USE_NATIVE_THREAD
    ptr = get_ip(ip_obj);
    DUMP2("invoke status: ptr->tk_thread_id %p", ptr->tk_thread_id);
    DUMP2("invoke status: Tcl_GetCurrentThread %p", Tcl_GetCurrentThread());
#else
    DUMP2("status: Tcl_GetCurrentThread %p", Tcl_GetCurrentThread());
#endif
    DUMP2("status: eventloopt_thread %"PRIxVALUE, eventloop_thread);

    if (
#ifdef RUBY_USE_NATIVE_THREAD
	(ptr->tk_thread_id == 0 || ptr->tk_thread_id == Tcl_GetCurrentThread())
	&&
#endif
	(NIL_P(eventloop_thread) || current == eventloop_thread)
	) {
        if (NIL_P(eventloop_thread)) {
            DUMP2("invoke from thread:%"PRIxVALUE" but no eventloop", current);
        } else {
            DUMP2("invoke from current eventloop %"PRIxVALUE, current);
        }
        result = ip_invoke_real(argc, argv, ip_obj);
        if (rb_obj_is_kind_of(result, rb_eException)) {
            rb_exc_raise(result);
        }
        return result;
    }

    DUMP2("invoke from thread %"PRIxVALUE" (NOT current eventloop)", current);

    thr_crit_bup = rb_thread_critical;
    rb_thread_critical = Qtrue;


    av = alloc_invoke_arguments(argc, argv);


    alloc_done = RbTk_ALLOC_N(int, 1);
#if 0
    Tcl_Preserve((ClientData)alloc_done);
#endif
    *alloc_done = 0;


    ivq = RbTk_ALLOC_N(struct invoke_queue, 1);
#if 0
    Tcl_Preserve((ClientData)ivq);
#endif


    result = rb_ary_new3(1, Qnil);


    ivq->done = alloc_done;
    ivq->argc = argc;
    ivq->argv = av;
    ivq->interp = ip_obj;
    ivq->result = result;
    ivq->thread = current;
    ivq->safe_level = rb_safe_level();
    ivq->ev.proc = invoke_queue_handler;


    DUMP1("add handler");
#ifdef RUBY_USE_NATIVE_THREAD
    if (ptr->tk_thread_id) {

      Tcl_ThreadQueueEvent(ptr->tk_thread_id, (Tcl_Event*)ivq, position);
      Tcl_ThreadAlert(ptr->tk_thread_id);
    } else if (tk_eventloop_thread_id) {


      Tcl_ThreadQueueEvent(tk_eventloop_thread_id,
			   (Tcl_Event*)ivq, position);
      Tcl_ThreadAlert(tk_eventloop_thread_id);
    } else {

      Tcl_QueueEvent((Tcl_Event*)ivq, position);
    }
#else

    Tcl_QueueEvent((Tcl_Event*)ivq, position);
#endif

    rb_thread_critical = thr_crit_bup;


    t.tv_sec  = 0;
    t.tv_usec = (long)((EVENT_HANDLER_TIMEOUT)*1000.0);

    DUMP2("ivq wait for handler (current thread:%"PRIxVALUE")", current);
    while(*alloc_done >= 0) {


      rb_thread_wait_for(t);
      DUMP2("*** ivq wakeup (current thread:%"PRIxVALUE")", current);
      DUMP2("***          (eventloop thread:%"PRIxVALUE")", eventloop_thread);
      if (NIL_P(eventloop_thread)) {
	DUMP1("*** ivq lost eventloop thread");
	break;
      }
    }
    DUMP2("back from handler (current thread:%"PRIxVALUE")", current);


    ret = RARRAY_PTR(result)[0];
#if 0
    Tcl_EventuallyFree((ClientData)alloc_done, TCL_DYNAMIC);
#else
#if 0
    Tcl_Release((ClientData)alloc_done);
#else

    ckfree((char*)alloc_done);
#endif
#endif

#if 0
#if 0
    Tcl_EventuallyFree((ClientData)ivq, TCL_DYNAMIC);
#else
#if 0
    Tcl_Release(ivq);
#else
    ckfree((char*)ivq);
#endif
#endif
#endif


    free_invoke_arguments(argc, av);


    if (rb_obj_is_kind_of(ret, rb_eException)) {
        DUMP1("raise exception");

	rb_exc_raise(rb_exc_new3(rb_obj_class(ret),
				 rb_funcallv(ret, ID_to_s, 0, 0)));
    }

    DUMP1("exit ip_invoke");
    return ret;
}
