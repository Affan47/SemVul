setTrackVisibility(int i, bool show)
{
  QString x = show?"show": "hide";
  QStringList scriptStr;
  scriptStr
    << QString("trks[%1].%2();").arg(i).arg(x)
    ;
  evaluateJS(scriptStr);
}
