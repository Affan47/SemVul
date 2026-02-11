pthread_create (pthread_t *__restrict thread,
			   __const pthread_attr_t *__restrict attr,
			   void *(*start_routine) (void *),
			   void *__restrict arg)
{
  FUNCTION_NAME;
  struct __pthread_create_info_t * __args = (struct __pthread_create_info_t*) malloc(sizeof(struct __pthread_create_info_t));
  __args->func = start_routine;
  __args->arg = arg;

  if(!libpthread_create)
    INTERCEPT("pthread_create", libpthread_create);


  return libpthread_create(thread, attr, __pthread_new_thread, __args);
}
