WebContents::~WebContents() {

  if (managed_web_contents()) {
    managed_web_contents()->GetView()->SetDelegate(nullptr);

    RenderViewDeleted(web_contents()->GetRenderViewHost());

    if (type_ == Type::BROWSER_WINDOW && owner_window()) {


      for (ExtendedWebContentsObserver& observer : observers_)
        observer.OnCloseContents();


      WebContentsDestroyed();
    } else if (Browser::Get()->is_shutting_down()) {

      DestroyWebContents(false );
    } else {


      DestroyWebContents(!IsGuest() );


      WebContentsDestroyed();
    }
  }
}
