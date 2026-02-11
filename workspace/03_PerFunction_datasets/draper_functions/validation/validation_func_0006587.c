updateCodecParameter(
  const DcmCodec *aCodec,
  const DcmCodecParameter *aCodecParameter)
{
  if ((aCodec == NULL)||(aCodecParameter == NULL)) return EC_IllegalParameter;
#ifdef WITH_THREADS
  if (! codecLock.initialized()) return EC_IllegalCall;
#endif

  OFCondition result = EC_Normal;

#ifdef WITH_THREADS
  OFReadWriteLocker locker(codecLock);
  if (0 == locker.wrlock())
  {
#endif
    OFListIterator(DcmCodecList *) first = registeredCodecs.begin();
    OFListIterator(DcmCodecList *) last = registeredCodecs.end();
    while (first != last)
    {
      if ((*first)->codec == aCodec) (*first)->codecParameter = aCodecParameter;
      ++first;
    }
#ifdef WITH_THREADS
  } else result = EC_IllegalCall;
#endif
  return result;
}
