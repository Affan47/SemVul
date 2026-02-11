pdf_print_dict(struct pdf_dict *dict, unsigned long depth)
{
    struct pdf_dict_node *node;

    for (node = dict->nodes; node != NULL; node = node->next) {
        if (node->type == PDF_DICT_STRING) {
            cli_errmsg("dict[%lu][%s]: %s\n", depth, node->key, (char *)(node->value));
        } else if (node->type == PDF_DICT_ARRAY) {
            cli_errmsg("dict[%lu][%s]: Array =>\n", depth, node->key);
            pdf_print_array((struct pdf_array *)(node->value), depth);
        } else if (node->type == PDF_DICT_DICT) {
            pdf_print_dict((struct pdf_dict *)(node->value), depth+1);
        }
    }
}
