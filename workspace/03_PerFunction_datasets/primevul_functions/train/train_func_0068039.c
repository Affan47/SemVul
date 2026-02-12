LoadWatcher(ScriptContext* context,
  LoadWatcher(content::RenderFrame* frame,
              const base::Callback<void(bool)>& callback)
      : content::RenderFrameObserver(frame), callback_(callback) {}

  void DidCreateDocumentElement() override {


    base::Callback<void(bool)> callback = callback_;
    delete this;
    callback.Run(true);
   }
