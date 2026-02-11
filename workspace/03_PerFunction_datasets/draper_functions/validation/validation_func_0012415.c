alBufferfv(ALuint buffer, ALenum eParam, const ALfloat* flValues)
{
    ALCcontext    *pContext;
    ALCdevice     *device;

    pContext = GetContextRef();
    if(!pContext) return;

    device = pContext->Device;
    if(!flValues)
        alSetError(pContext, AL_INVALID_VALUE);
    else if(LookupBuffer(device, buffer) == NULL)
        alSetError(pContext, AL_INVALID_NAME);
    else
    {
        switch(eParam)
        {
        default:
            alSetError(pContext, AL_INVALID_ENUM);
            break;
        }
    }

    ALCcontext_DecRef(pContext);
}
