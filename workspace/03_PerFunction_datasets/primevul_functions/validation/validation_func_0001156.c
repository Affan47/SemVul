PCREglobals::PCREglobals() {
  jit_stack = pcre_jit_stack_alloc(32768, 524288);


  preg_backtrace_limit = RuntimeOption::PregBacktraceLimit;
  preg_recursion_limit = RuntimeOption::PregRecursionLimit;
}
