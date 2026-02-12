QString Utility::GetEnvironmentVar(const QString &variable_name)
{


    QRegularExpression search_for_name("^" + QRegularExpression::escape(variable_name) + "=");
    QString variable = QProcess::systemEnvironment().filter(search_for_name).value(0);

    if (!variable.isEmpty()) {
        return variable.split("=")[ 1 ];
    } else {
        return QString();
    }
}
