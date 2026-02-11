loadScript(const QString &path, const QString &prefix)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        kError() << "failed to open script file" << path;
        return false;
    }

    QTextStream buffer(&file);
    QString tmp(buffer.readAll());

    QScriptEngine *engine = AnimationScriptEngine::globalEngine();
    engine->pushContext();
    s_prefix = prefix;
    QScriptValue def(engine->evaluate(tmp, path));
    s_prefix.clear();
    engine->popContext();
    if (engine->hasUncaughtException()) {
        const QScriptValue error = engine->uncaughtException();
        QString file = error.property("fileName").toString();
        const QString failureMsg = QString("Error in %1 on line %2.\n%3")
                                          .arg(file)
                                          .arg(error.property("lineNumber").toString())
                                          .arg(error.toString());
        kError() << failureMsg;
        return false;
    }

    return true;
}
