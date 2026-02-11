getValueProperty(ExecState *exec, int token) const
{
  StyleSheetImpl &styleSheet = *m_impl;
  switch (token) {
  case Type:
    return jsString(styleSheet.type());
  case Disabled:
    return jsBoolean(styleSheet.disabled());
  case OwnerNode:
    return getDOMNode(exec,styleSheet.ownerNode());
  case ParentStyleSheet:
    return getDOMStyleSheet(exec,styleSheet.parentStyleSheet());
  case Href:
    return getStringOrNull(styleSheet.href());
  case Title:
    return jsString(styleSheet.title());
  case Media:
    return getDOMMediaList(exec, styleSheet.media());
  }
  return 0;
}
