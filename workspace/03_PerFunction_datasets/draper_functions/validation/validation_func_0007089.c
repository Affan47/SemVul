check_update(GBDATA *gbdummy)
{
    AWUSE(gbdummy);
    AP_UPDATE_FLAGS flags;
    char *name;
    GB_ERROR error;
    if (!this->tree_static) return 0;
    GB_transaction dummy(gb_main);

    if (!this->tree_root) {
        flags = AP_UPDATE_ERROR;
    }
    else {
        flags = this->tree_root->check_update();
        switch (flags){
            case AP_UPDATE_OK:
            case AP_UPDATE_ERROR:
                return flags;
            case AP_UPDATE_RELOADED:
                name = strdup(this->tree_static->tree_name);
                error = this->load(gb_main, name, 1, 0);
                if (error) aw_message(error);
                free(name);
                this->exports.resize = 1;
                break;
            case AP_UPDATE_RELINKED:
                error = this->tree_root->relink();
                if (error) aw_message(error);
                else    this->tree_root->compute_tree(gb_main);
                break;
        }
    }
    return (int)flags;
}
