Ns_ThreadCreate(Ns_ThreadProc *proc, void *arg, long stacksize,
    	    	Ns_Thread *resultPtr)
{
    ThreadArg *argPtr;


    if (stacksize <= 0) {
    	stacksize = Ns_ThreadStackSize(0);
    }
    if (stacksize < stackmin) {
	stacksize = stackmin;
    }


    argPtr = ns_malloc(sizeof(ThreadArg));
    argPtr->proc = proc;
    argPtr->arg = arg;
    argPtr->flags = resultPtr ? 0 : FLAG_DETACHED;
    strcpy(argPtr->parent, Ns_ThreadGetName());
    NsCreateThread(argPtr, stacksize, resultPtr);
}
