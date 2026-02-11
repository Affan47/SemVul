verifyImage() {
  if (imageFile.empty() || templFile.empty()) {
    cerr << subst(_(
      "%1 verify: Not both --image and --template specified.\n"
      "(Attempt to deduce missing names failed.)\n"), binaryName);
    exit_tryHelp();
  }

  bistream* image;
  auto_ptr<bistream> imageDel(openForInput(image, imageFile));

  JigdoDescVec contents;
  JigdoDesc::ImageInfo* info;
  try {
    bistream* templ;
    auto_ptr<bistream> templDel(openForInput(templ, templFile));

    if (JigdoDesc::isTemplate(*templ) == false)
      optReporter->info(
          _("Warning: This does not seem to be a template file"));

    JigdoDesc::seekFromEnd(*templ);
    *templ >> contents;
    if (!*templ) {
      string err = subst(_("%1 verify: %2"), binaryName, strerror(errno));
      optReporter->error(err);
      return 3;
    }
    info = dynamic_cast<JigdoDesc::ImageInfo*>(contents.back());
    if (info == 0) {
      string err = subst(_("%1 verify: Invalid template data - "
                           "corrupted file?"), binaryName);
      optReporter->error(err);
      return 3;
    }
  } catch (JigdoDescError e) {
    string err = subst(_("%1: %2"), binaryName, e.message);
    optReporter->error(err);
    return 3;
  }

  MD5Sum md;
  md.updateFromStream(*image, info->size(), readAmount, *optReporter);
  md.finish();
  if (*image) {
    image->get();
    if (image->eof() && md == info->md5()) {
      optReporter->info(_("OK: Checksums match, image is good!"));
      return 0;
    }
  }
  optReporter->error(_(
      "ERROR: Checksums do not match, image might be corrupted!"));
  return 2;
}
