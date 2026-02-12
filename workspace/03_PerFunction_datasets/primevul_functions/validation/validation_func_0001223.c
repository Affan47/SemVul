void Strobelight::surpriseAll() {
  RequestInfo::ExecutePerRequest(
    [] (RequestInfo* t) {


      if (!isXenonActive()) {


        t->m_reqInjectionData.setFlag(XenonSignalFlag);
      }
    }
  );
}
