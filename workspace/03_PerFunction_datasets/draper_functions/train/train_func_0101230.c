move_tree_2_ssr(AP_tree *node){
    AWT_species_set *ss;
    if (node->is_leaf){
        this->add(node->name);
        ss = new AWT_species_set(node,this,node->name);

    }else{
        AWT_species_set *ls = this->move_tree_2_ssr(node->leftson);
        AWT_species_set *rs = this->move_tree_2_ssr(node->rightson);
        ss = new AWT_species_set(node,this,ls,rs);
        this->add(ss);
    }
    return ss;
}
