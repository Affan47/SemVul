void ModularFrameDecoder::MaybeDropFullImage() {
  if (full_image.transform.empty() && !have_something) {
    use_full_image = false;
    for (auto& ch : full_image.channel) {

      ch.plane = Plane<pixel_type>();
    }
  }
}
