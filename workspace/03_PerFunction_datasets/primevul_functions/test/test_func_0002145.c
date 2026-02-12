pcre2_jit_compile(pcre2_code *code, uint32_t options)
{
pcre2_real_code *re = (pcre2_real_code *)code;
#ifdef SUPPORT_JIT
executable_functions *functions;
static int executable_allocator_is_working = 0;
#endif

if (code == NULL)
  return PCRE2_ERROR_NULL;

if ((options & ~PUBLIC_JIT_COMPILE_OPTIONS) != 0)
  return PCRE2_ERROR_JIT_BADOPTION;


#ifdef SUPPORT_JIT
functions = (executable_functions *)re->executable_jit;
#endif

if ((options & PCRE2_JIT_INVALID_UTF) != 0)
  {
  if ((re->overall_options & PCRE2_MATCH_INVALID_UTF) == 0)
    {
#ifdef SUPPORT_JIT
    if (functions != NULL) return PCRE2_ERROR_JIT_BADOPTION;
#endif
    re->overall_options |= PCRE2_MATCH_INVALID_UTF;
    }
  }


#ifndef SUPPORT_JIT
return PCRE2_ERROR_JIT_BADOPTION;
#else


if ((re->flags & PCRE2_NOJIT) != 0) return 0;

if (executable_allocator_is_working == 0)
  {


  void *ptr = SLJIT_MALLOC_EXEC(32, NULL);

  executable_allocator_is_working = -1;

  if (ptr != NULL)
    {
    SLJIT_FREE_EXEC(((sljit_u8*)(ptr)) + SLJIT_EXEC_OFFSET(ptr), NULL);
    executable_allocator_is_working = 1;
    }
  }

if (executable_allocator_is_working < 0)
  return PCRE2_ERROR_NOMEMORY;

if ((re->overall_options & PCRE2_MATCH_INVALID_UTF) != 0)
  options |= PCRE2_JIT_INVALID_UTF;

if ((options & PCRE2_JIT_COMPLETE) != 0 && (functions == NULL
    || functions->executable_funcs[0] == NULL)) {
  uint32_t excluded_options = (PCRE2_JIT_PARTIAL_SOFT | PCRE2_JIT_PARTIAL_HARD);
  int result = jit_compile(code, options & ~excluded_options);
  if (result != 0)
    return result;
  }

if ((options & PCRE2_JIT_PARTIAL_SOFT) != 0 && (functions == NULL
    || functions->executable_funcs[1] == NULL)) {
  uint32_t excluded_options = (PCRE2_JIT_COMPLETE | PCRE2_JIT_PARTIAL_HARD);
  int result = jit_compile(code, options & ~excluded_options);
  if (result != 0)
    return result;
  }

if ((options & PCRE2_JIT_PARTIAL_HARD) != 0 && (functions == NULL
    || functions->executable_funcs[2] == NULL)) {
  uint32_t excluded_options = (PCRE2_JIT_COMPLETE | PCRE2_JIT_PARTIAL_SOFT);
  int result = jit_compile(code, options & ~excluded_options);
  if (result != 0)
    return result;
  }

return 0;

#endif
}
