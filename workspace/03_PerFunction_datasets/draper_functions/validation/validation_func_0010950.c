moveItem(Item item, int movement) {

    int index = find(item);
    const size_t size = m_item_list.size();

    if (index < 0 || (movement % static_cast<signed>(size)) == 0) {
        return;
    }

    int newindex = (index + movement) % static_cast<signed>(size);
    if (newindex < 0)
        newindex += size;

    ItemList::iterator it = std::find(begin(), end(), item);
    m_item_list.erase(it);

    for (it = begin(); newindex >= 0; ++it, --newindex) {
        if (newindex == 0) {
            break;
        }
    }

    m_item_list.insert(it, item);
    repositionItems();
}
