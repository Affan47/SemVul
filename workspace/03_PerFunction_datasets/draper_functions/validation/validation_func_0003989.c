updateCategory(CategoryItem *category)
{

    int id = category->id();
    if (id < 0)
        return false;


    if (!category->isDirty())
        return true;

    QHash<int, QString> where;
    where.insert(Constants::CATEGORY_ID, QString("=%1").arg(category->id()));
    QSqlQuery query(database());
    query.prepare(prepareUpdateQuery(Constants::Table_CATEGORIES, QList<int>()
                                     << Constants::CATEGORY_MIME
                                     << Constants::CATEGORY_PASSWORD
                                     << Constants::CATEGORY_ISVALID
                                     << Constants::CATEGORY_PARENT
                                     << Constants::CATEGORY_SORT_ID
                                     << Constants::CATEGORY_THEMEDICON
                                     << Constants::CATEGORY_EXTRAXML
                                     << Constants::CATEGORY_UUID

                                     , where));
    query.bindValue(0, category->mime());
    query.bindValue(1, category->cryptedPassword());
    query.bindValue(2, category->data(CategoryItem::DbOnly_IsValid).toInt());
    query.bindValue(3, category->data(CategoryItem::DbOnly_ParentId));
    query.bindValue(4, category->data(CategoryItem::SortId));
    query.bindValue(5, category->data(CategoryItem::ThemedIcon));
    query.bindValue(6, category->data(CategoryItem::ExtraXml));
    query.bindValue(7, category->data(CategoryItem::Uuid));

    if (!query.exec()) {
        LOG_QUERY_ERROR(query);
        return false;
    }
    query.finish();


    if (!saveCategoryLabels(category))
        return false;
    category->setDirty(false);
    return true;
}
