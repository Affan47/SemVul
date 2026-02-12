CallResult<Handle<JSArray>> JSObject::getOwnPropertyKeys(
    Handle<JSObject> selfHandle,
    Runtime *runtime,
    OwnKeysFlags okFlags) {
  assert(
      (okFlags.getIncludeNonSymbols() || okFlags.getIncludeSymbols()) &&
      "Can't exclude symbols and strings");
  if (LLVM_UNLIKELY(
          selfHandle->flags_.lazyObject || selfHandle->flags_.proxyObject)) {
    if (selfHandle->flags_.proxyObject) {
      CallResult<PseudoHandle<JSArray>> proxyRes =
          JSProxy::ownPropertyKeys(selfHandle, runtime, okFlags);
      if (LLVM_UNLIKELY(proxyRes == ExecutionStatus::EXCEPTION)) {
        return ExecutionStatus::EXCEPTION;
      }
      return runtime->makeHandle(std::move(*proxyRes));
    }
    assert(selfHandle->flags_.lazyObject && "descriptor flags are impossible");
    initializeLazyObject(runtime, selfHandle);
  }

  auto range = getOwnIndexedRange(selfHandle.get(), runtime);


  uint32_t capacity = okFlags.getIncludeNonSymbols()
      ? (selfHandle->clazz_.get(runtime)->getNumProperties() + range.second -
         range.first)
      : 0;

  auto arrayRes = JSArray::create(runtime, capacity, 0);
  if (LLVM_UNLIKELY(arrayRes == ExecutionStatus::EXCEPTION)) {
    return ExecutionStatus::EXCEPTION;
  }
  auto array = runtime->makeHandle(std::move(*arrayRes));


  llvh::Optional<Handle<JSArray>> hostObjectSymbols;
  size_t hostObjectSymbolCount = 0;


  llvh::SmallSet<SymbolID::RawType, 16> dedupSet;


  uint32_t index = 0;


  MutableHandle<> tmpHandle{runtime};


  uint32_t numIndexed = 0;


  llvh::SmallVector<uint32_t, 8> indexNames{};


  if (okFlags.getIncludeNonSymbols()) {

    if (LLVM_UNLIKELY(selfHandle->flags_.hostObject)) {
      assert(
          range.first == range.second &&
          "Host objects cannot own indexed range");
      auto hostSymbolsRes =
          vmcast<HostObject>(selfHandle.get())->getHostPropertyNames();
      if (hostSymbolsRes == ExecutionStatus::EXCEPTION) {
        return ExecutionStatus::EXCEPTION;
      }
      if ((hostObjectSymbolCount = (**hostSymbolsRes)->getEndIndex()) != 0) {
        Handle<JSArray> hostSymbols = *hostSymbolsRes;
        hostObjectSymbols = std::move(hostSymbols);
        capacity += hostObjectSymbolCount;
      }
    }


    GCScopeMarkerRAII marker{runtime};
    for (auto i = range.first; i != range.second; ++i) {
      auto res = getOwnIndexedPropertyFlags(selfHandle.get(), runtime, i);
      if (!res)
        continue;


      if (!okFlags.getIncludeNonEnumerable() && !res->enumerable)
        continue;

      tmpHandle = HermesValue::encodeDoubleValue(i);
      JSArray::setElementAt(array, runtime, index++, tmpHandle);
      marker.flush();
    }

    numIndexed = index;

    HiddenClass::forEachProperty(
        runtime->makeHandle(selfHandle->clazz_),
        runtime,
        [runtime,
         okFlags,
         array,
         hostObjectSymbolCount,
         &index,
         &indexNames,
         &tmpHandle,
         &dedupSet](SymbolID id, NamedPropertyDescriptor desc) {
          if (!isPropertyNamePrimitive(id)) {
            return;
          }


          if (!okFlags.getIncludeNonEnumerable()) {
            if (!desc.flags.enumerable)
              return;
          }


          if (LLVM_UNLIKELY(hostObjectSymbolCount > 0)) {
            dedupSet.insert(id.unsafeGetRaw());
          }


          auto propNameAsIndex = toArrayIndex(
              runtime->getIdentifierTable().getStringView(runtime, id));
          if (LLVM_UNLIKELY(propNameAsIndex)) {
            indexNames.push_back(*propNameAsIndex);
            return;
          }

          tmpHandle = HermesValue::encodeStringValue(
              runtime->getStringPrimFromSymbolID(id));
          JSArray::setElementAt(array, runtime, index++, tmpHandle);
        });


    if (LLVM_UNLIKELY(hostObjectSymbols)) {
      for (size_t i = 0; i < hostObjectSymbolCount; ++i) {
        assert(
            (*hostObjectSymbols)->at(runtime, i).isSymbol() &&
            "Host object needs to return array of SymbolIDs");
        marker.flush();
        SymbolID id = (*hostObjectSymbols)->at(runtime, i).getSymbol();
        if (dedupSet.count(id.unsafeGetRaw()) == 0) {
          dedupSet.insert(id.unsafeGetRaw());

          assert(
              !InternalProperty::isInternal(id) &&
              "host object returned reserved symbol");
          auto propNameAsIndex = toArrayIndex(
              runtime->getIdentifierTable().getStringView(runtime, id));
          if (LLVM_UNLIKELY(propNameAsIndex)) {
            indexNames.push_back(*propNameAsIndex);
            continue;
          }
          tmpHandle = HermesValue::encodeStringValue(
              runtime->getStringPrimFromSymbolID(id));
          JSArray::setElementAt(array, runtime, index++, tmpHandle);
        }
      }
    }
  }


  if (okFlags.getIncludeSymbols()) {
    MutableHandle<SymbolID> idHandle{runtime};
    HiddenClass::forEachProperty(
        runtime->makeHandle(selfHandle->clazz_),
        runtime,
        [runtime, okFlags, array, &index, &idHandle](
            SymbolID id, NamedPropertyDescriptor desc) {
          if (!isSymbolPrimitive(id)) {
            return;
          }

          if (!okFlags.getIncludeNonEnumerable()) {
            if (!desc.flags.enumerable)
              return;
          }
          idHandle = id;
          JSArray::setElementAt(array, runtime, index++, idHandle);
        });
  }


  uint32_t endNamed = index;


  auto cr = JSArray::setLength(
      array, runtime, endNamed + indexNames.size(), PropOpFlags{});
  (void)cr;
  assert(
      cr != ExecutionStatus::EXCEPTION && *cr && "JSArray::setLength() failed");


  if (LLVM_LIKELY(indexNames.empty()))
    return array;


  std::sort(indexNames.begin(), indexNames.end());


  JSArray::setStorageEndIndex(array, runtime, endNamed + indexNames.size());


  for (uint32_t last = endNamed, toLast = array->getEndIndex();
       last != numIndexed;) {
    --last;
    --toLast;
    tmpHandle = array->at(runtime, last);
    JSArray::setElementAt(array, runtime, toLast, tmpHandle);
  }


  for (uint32_t toLast = numIndexed + indexNames.size(),
                indexNamesLast = indexNames.size();
       toLast != 0;) {
    if (numIndexed) {
      uint32_t a = (uint32_t)array->at(runtime, numIndexed - 1).getNumber();
      uint32_t b;

      if (indexNamesLast && (b = indexNames[indexNamesLast - 1]) > a) {
        tmpHandle = HermesValue::encodeDoubleValue(b);
        --indexNamesLast;
      } else {
        tmpHandle = HermesValue::encodeDoubleValue(a);
        --numIndexed;
      }
    } else {
      assert(indexNamesLast && "prematurely ran out of source values");
      tmpHandle =
          HermesValue::encodeDoubleValue(indexNames[indexNamesLast - 1]);
      --indexNamesLast;
    }

    --toLast;
    JSArray::setElementAt(array, runtime, toLast, tmpHandle);
  }

  return array;
}
