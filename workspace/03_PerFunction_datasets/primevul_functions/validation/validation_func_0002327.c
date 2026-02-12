JSObject::checkPropertyUpdate(
    Runtime *runtime,
    const PropertyFlags currentFlags,
    DefinePropertyFlags dpFlags,
    const HermesValue curValueOrAccessor,
    Handle<> valueOrAccessor,
    PropOpFlags opFlags) {

  if (dpFlags.isEmpty())
    return std::make_pair(PropertyUpdateStatus::done, currentFlags);

  assert(
      (!dpFlags.isAccessor() || (!dpFlags.setWritable && !dpFlags.writable)) &&
      "can't set both accessor and writable");
  assert(
      !dpFlags.enableInternalSetter &&
      "cannot change the value of internalSetter");


  if ((!dpFlags.setEnumerable ||
       dpFlags.enumerable == currentFlags.enumerable) &&
      (!dpFlags.setConfigurable ||
       dpFlags.configurable == currentFlags.configurable)) {
    if (dpFlags.isAccessor()) {
      if (currentFlags.accessor) {
        auto *curAccessor = vmcast<PropertyAccessor>(curValueOrAccessor);
        auto *newAccessor = vmcast<PropertyAccessor>(valueOrAccessor.get());

        if ((!dpFlags.setGetter ||
             curAccessor->getter == newAccessor->getter) &&
            (!dpFlags.setSetter ||
             curAccessor->setter == newAccessor->setter)) {
          return std::make_pair(PropertyUpdateStatus::done, currentFlags);
        }
      }
    } else {
      if (!currentFlags.accessor &&
          (!dpFlags.setValue ||
           isSameValue(curValueOrAccessor, valueOrAccessor.get())) &&
          (!dpFlags.setWritable || dpFlags.writable == currentFlags.writable)) {
        return std::make_pair(PropertyUpdateStatus::done, currentFlags);
      }
    }
  }


  if (!currentFlags.configurable) {

    if (dpFlags.configurable) {
      if (opFlags.getThrowOnError()) {
        return runtime->raiseTypeError(
            "property is not configurable");
      }
      return std::make_pair(PropertyUpdateStatus::failed, PropertyFlags{});
    }


    if (dpFlags.setEnumerable &&
        dpFlags.enumerable != currentFlags.enumerable) {
      if (opFlags.getThrowOnError()) {
        return runtime->raiseTypeError(
            "property is not configurable");
      }
      return std::make_pair(PropertyUpdateStatus::failed, PropertyFlags{});
    }
  }

  PropertyFlags newFlags = currentFlags;


  if (!(dpFlags.setValue || dpFlags.setWritable || dpFlags.setGetter ||
        dpFlags.setSetter)) {

  }


  else if (currentFlags.accessor != dpFlags.isAccessor()) {
    if (!currentFlags.configurable) {
      if (opFlags.getThrowOnError()) {
        return runtime->raiseTypeError(
            "property is not configurable");
      }
      return std::make_pair(PropertyUpdateStatus::failed, PropertyFlags{});
    }


    newFlags.writable = 0;


    if (!dpFlags.isAccessor())
      dpFlags.setValue = 1;
  }

  else if (!currentFlags.accessor) {
    if (!currentFlags.configurable) {
      if (!currentFlags.writable) {

        if (dpFlags.writable) {
          if (opFlags.getThrowOnError()) {
            return runtime->raiseTypeError(
                "property is not configurable");
          }
          return std::make_pair(PropertyUpdateStatus::failed, PropertyFlags{});
        }


        if (dpFlags.setValue &&
            !isSameValue(curValueOrAccessor, valueOrAccessor.get())) {
          if (opFlags.getThrowOnError()) {
            return runtime->raiseTypeError(
                "property is not writable");
          }
          return std::make_pair(PropertyUpdateStatus::failed, PropertyFlags{});
        }
      }
    }
  }

  else {
    auto *curAccessor = vmcast<PropertyAccessor>(curValueOrAccessor);
    auto *newAccessor = vmcast<PropertyAccessor>(valueOrAccessor.get());


    if (!currentFlags.configurable) {
      if ((dpFlags.setGetter && newAccessor->getter != curAccessor->getter) ||
          (dpFlags.setSetter && newAccessor->setter != curAccessor->setter)) {
        if (opFlags.getThrowOnError()) {
          return runtime->raiseTypeError(
              "property is not configurable");
        }
        return std::make_pair(PropertyUpdateStatus::failed, PropertyFlags{});
      }
    }


    if (!dpFlags.setGetter)
      newAccessor->getter.set(
          runtime, curAccessor->getter, &runtime->getHeap());
    if (!dpFlags.setSetter)
      newAccessor->setter.set(
          runtime, curAccessor->setter, &runtime->getHeap());
  }


  if (dpFlags.setEnumerable)
    newFlags.enumerable = dpFlags.enumerable;
  if (dpFlags.setWritable)
    newFlags.writable = dpFlags.writable;
  if (dpFlags.setConfigurable)
    newFlags.configurable = dpFlags.configurable;

  if (dpFlags.setValue)
    newFlags.accessor = false;
  else if (dpFlags.isAccessor())
    newFlags.accessor = true;
  else
    return std::make_pair(PropertyUpdateStatus::done, newFlags);

  return std::make_pair(PropertyUpdateStatus::needSet, newFlags);
}
