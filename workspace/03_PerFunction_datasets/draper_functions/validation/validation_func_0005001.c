posix_detach_thread_function(void*c)
{
thread_traits<posix> ::_Dtype*ct=
(thread_traits<posix> ::_Dtype*)c;
condition_counter<posix> *counter= ct->counter;
try{
ct->operator()();
}catch(...){
ct->exit();
}
if(counter)
counter->decrease();
return NULL;
}
