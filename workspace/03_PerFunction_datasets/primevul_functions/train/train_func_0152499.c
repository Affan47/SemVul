AbstractWebApplication::~AbstractWebApplication()
{

    qDeleteAll(sessions_);
}
