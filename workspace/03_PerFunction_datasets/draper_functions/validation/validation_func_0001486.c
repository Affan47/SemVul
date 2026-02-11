saveOptions(QSettings &settings, const QString &prefix, const QList<FormatOption> &options) {
  for (int i=0; i<options.size(); i++) {
    QString kp = prefix + "." + options[i].getName();
    QString k1 = kp + ".selected";
    QString k2 = kp + ".value";
    settings.setValue(k1, options[i].getSelected());
    settings.setValue(k2, options[i].getValue());
  }
}
