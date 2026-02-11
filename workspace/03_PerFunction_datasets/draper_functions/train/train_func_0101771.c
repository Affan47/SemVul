construct(ExecState *exec, const List &args)
{
  int numArgs = args.size();
  double value;

  if (numArgs == 0) {
    value = getCurrentUTCTime();
  } else if (numArgs == 1) {
    JSValue* arg0 = args[0];
    if (arg0->isObject(&DateInstance::info))
      value = static_cast<DateInstance*>(arg0)->internalValue()->toNumber(exec);
    else {
      JSValue* primitive = arg0->toPrimitive(exec);
      if (primitive->isString())
        value = parseDate(primitive->getString());
      else
        value = primitive->toNumber(exec);
    }
  } else {
    value = makeTimeFromList(exec, args, false);
  }

  DateInstance *ret = new DateInstance(exec->lexicalInterpreter()->builtinDatePrototype());
  ret->setInternalValue(jsNumber(timeClip(value)));
  return ret;
}
