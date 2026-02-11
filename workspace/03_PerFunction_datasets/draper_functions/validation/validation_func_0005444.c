GetFirstMediaContentDescription(
    const SessionDescription* sdesc, MediaType media_type) {
  const ContentInfo* content = GetFirstMediaContent(sdesc, media_type);
  const ContentDescription* description = content ? content->description : NULL;
  return static_cast<const MediaContentDescription*>(description);
}
