void WebContents::WebContentsDestroyed() {


  if (guest_delegate_)
    guest_delegate_->WillDestroy();


  RemoveFromWeakMap();


  MarkDestroyed();

  Emit("destroyed");


  if (IsGuest() && managed_web_contents()) {
    managed_web_contents()->ReleaseWebContents();
    ResetManagedWebContents(false);
  }


  base::ThreadTaskRunnerHandle::Get()->PostTask(FROM_HERE, GetDestroyClosure());
}
