void WebContents::RenderFrameDeleted(
    content::RenderFrameHost* render_frame_host) {


  auto it = frame_to_receivers_map_.find(render_frame_host);
  if (it == frame_to_receivers_map_.end())
    return;
  for (auto id : it->second)
    receivers_.Remove(id);
  frame_to_receivers_map_.erase(it);
}
