void WebContents::IncrementCapturerCount(gin_helper::Arguments* args) {
  gfx::Size size;
  bool stay_hidden = false;


  args->GetNext(&size);

  args->GetNext(&stay_hidden);

  web_contents()->IncrementCapturerCount(size, stay_hidden);
}
