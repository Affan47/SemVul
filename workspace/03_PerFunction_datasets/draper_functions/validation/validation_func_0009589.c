init_process_context(PCB* target) {
    char* proc_sp = NULL;
    PCB* newPCB = target;
    if (setjmp(kernel_buf) == 0) {
      proc_sp = newPCB->stack;
#ifdef i386
      __asm__("movl %0,%%esp" :"=m" (proc_sp));
#endif
#ifdef __amd64
      __asm__("movl %0,%%esp" :"=m" (proc_sp));
#endif
#ifdef __sparc
      _set_sp( proc_sp );
#endif
      if (setjmp(newPCB->context) == 0) {
        longjmp(kernel_buf, 1);
      } else {
        void (*tmp) ();
        tmp = (void*) current_process->process_code;
	atomic(0);
        tmp();
      }
    }
}
