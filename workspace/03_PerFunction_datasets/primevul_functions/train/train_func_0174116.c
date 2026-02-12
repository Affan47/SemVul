static JSITHREADRET NewInterpThread(void* iPtr)
{
    int rc = JSI_OK;
    InterpObj *udf = (InterpObj *)iPtr;
    Jsi_Interp *interp = udf->subinterp;
    interp->threadId = Jsi_CurrentThread();
    if (interp->scriptStr)
        rc = Jsi_EvalString(interp, interp->scriptStr, 0);
    else if (interp->scriptFile) {
        if (!interp->debugOpts.debugCallback)
            Jsi_EvalFile(interp, interp->scriptFile, 0);
    } else {
        Jsi_LogBug("no eval");
    }
    if (rc != JSI_OK) {
        Jsi_LogError("eval failure");
        interp->threadErrCnt++;
        if (Jsi_MutexLock(interp, interp->Mutex) != JSI_OK)
            return NULL;
        Jsi_MutexUnlock(interp, interp->Mutex);
    }
    interpObjErase(udf);
#ifndef __WIN32

    pthread_detach(pthread_self());
    return NULL;
#endif
}
