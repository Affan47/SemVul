void WebContents::RenderViewDeleted(content::RenderViewHost* render_view_host) {


  Emit("render-view-deleted", render_view_host->GetProcess()->GetID());

  if (-1 == currently_committed_process_id_ ||
      render_view_host->GetProcess()->GetID() ==
          currently_committed_process_id_) {
    currently_committed_process_id_ = -1;


    Emit("current-render-view-deleted",
         render_view_host->GetProcess()->GetID());
  }
}
