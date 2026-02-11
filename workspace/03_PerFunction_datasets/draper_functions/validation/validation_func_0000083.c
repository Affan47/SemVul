GetVisibleTypeName() const
{
  switch (this->GetTarget()->GetType()) {
    case cmTarget::STATIC_LIBRARY:
      return "static library";
    case cmTarget::SHARED_LIBRARY:
      return "shared library";
    case cmTarget::MODULE_LIBRARY:
      if (this->GetTarget()->IsCFBundleOnApple())
        return "CFBundle shared module";
      else
        return "shared module";
    case cmTarget::EXECUTABLE:
      return "executable";
    default:
      return 0;
  }
}
