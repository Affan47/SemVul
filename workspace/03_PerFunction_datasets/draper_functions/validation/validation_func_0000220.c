createNamespace(const Core::TokenNamespace &ns, QStandardItem *parent = 0)
    {
        if (!parent)
            parent = q->invisibleRootItem();


        QString fullNs = parent->data(TOKEN_UID).toString();

        QStandardItem *item = new QStandardItem;
        fullNs.isEmpty() ? fullNs = ns.uid() : fullNs += "." + ns.uid();
        item->setData(fullNs, TOKEN_UID);
        if (!ns.tooltip().isEmpty()) {
            item->setToolTip(ns.tooltip());
            if (parent == q->invisibleRootItem()) {
                item->setText(QString("<span style=\"color:black;font-weight:bold\">%1</span><br />"
                                      "<span style=\"color:gray;font-size:small\">%2</span>")
                              .arg(ns.humanReadableName())
                              .arg(ns.tooltip().replace("/n", "<br />")));
            }
        } else {
            item->setText(ns.humanReadableName());
        }
        parent->appendRow(item);
        _tokensNamespaceToItem.insert(fullNs, item);

        foreach(const Core::TokenNamespace &child, ns.children())
            createNamespace(child, item);
    }
