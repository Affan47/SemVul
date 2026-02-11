availableActions(const QString& serviceName)
{

    QSet<QString> ret;
    QList<QContactActionDescriptor> actionDescriptors = QContactActionManager::instance()->actionDescriptors();
    for (int i = 0; i < actionDescriptors.size(); i++) {
        QContactActionDescriptor descriptor = actionDescriptors.at(i);
        if (serviceName.isEmpty() || serviceName == descriptor.serviceName()) {
            ret.insert(descriptor.actionName());
        }
    }

    return ret.toList();
}
