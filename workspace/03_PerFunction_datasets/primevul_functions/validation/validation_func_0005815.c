ElectronNavigationThrottle::WillStartRequest() {
  auto* handle = navigation_handle();
  auto* contents = handle->GetWebContents();
  if (!contents) {
    NOTREACHED();
    return PROCEED;
  }

  v8::Isolate* isolate = v8::Isolate::GetCurrent();
  v8::HandleScope scope(isolate);
  auto api_contents = electron::api::WebContents::From(isolate, contents);
  if (api_contents.IsEmpty()) {

    return PROCEED;
  }

  if (handle->IsRendererInitiated() && handle->IsInMainFrame() &&
      api_contents->EmitNavigationEvent("will-navigate", handle)) {
    return CANCEL;
  }
  return PROCEED;
}
