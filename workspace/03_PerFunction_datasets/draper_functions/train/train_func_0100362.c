RemovePacketComponent(int in_id) {
    string str;

    if (component_id_map.find(in_id) != component_id_map.end()) {
        return -1;
    }

    str = component_id_map[in_id];
    component_id_map.erase(component_id_map.find(in_id));
    component_str_map.erase(component_str_map.find(str));

    return 1;
}
