check_type_union_leafref(struct lys_type *type)
{
    uint8_t i;

    if ((type->base == LY_TYPE_UNION) && type->info.uni.count) {

        for (i = 0; i < type->info.uni.count; ++i) {
            switch (type->info.uni.types[i].base) {
            case LY_TYPE_LEAFREF:
                return 1;
            case LY_TYPE_UNION:
                if (check_type_union_leafref(&type->info.uni.types[i])) {
                    return 1;
                }
                break;
            default:
                break;
            }
        }

        return 0;
    }


    return type->der->has_union_leafref;
}
