category(int categoryId) const
{
    if (d->categories.contains(categoryId)) {
        return d->categories[categoryId];
    }

    return d->categories[InvalidCategory];
}
