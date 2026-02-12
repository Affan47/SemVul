bool WebContents::HandleKeyboardEvent(
    content::WebContents* source,
    const content::NativeWebKeyboardEvent& event) {
  if (type_ == Type::WEB_VIEW && embedder_) {

    return embedder_->HandleKeyboardEvent(source, event);
  } else {

    return CommonWebContentsDelegate::HandleKeyboardEvent(source, event);
  }
}
