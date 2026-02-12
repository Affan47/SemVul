lyp_deviation_apply_ext(struct lys_module *module)
{
    int i, j, k;
    struct lys_deviate *dev;
    struct lys_node *target;
    struct ly_set *extset;

    for (i = 0; i < module->deviation_size; i++) {
        target = NULL;
        extset = NULL;
        j = resolve_schema_nodeid(module->deviation[i].target_name, NULL, module, &extset, 0, 0);
        if (j == -1) {
            return EXIT_FAILURE;
        } else if (!extset) {

            ly_set_free(extset);
            continue;
        }
        target = extset->set.s[0];
        ly_set_free(extset);

        for (j = 0; j < module->deviation[i].deviate_size; j++) {
            dev = &module->deviation[i].deviate[j];
            if (!dev->ext_size) {

                continue;
            }


            if (dev->mod == LY_DEVIATE_DEL) {
                k = -1;
                while ((k = lys_ext_iter(dev->ext, dev->ext_size, k + 1, LYEXT_SUBSTMT_SELF)) != -1) {
                    if (lyp_deviate_del_ext(target, dev->ext[k])) {
                        return EXIT_FAILURE;
                    }
                }


                continue;
            } else {
                extset = ly_set_new();
                k = -1;
                while ((k = lys_ext_iter(dev->ext, dev->ext_size, k + 1, LYEXT_SUBSTMT_SELF)) != -1) {
                    ly_set_add(extset, dev->ext[k]->def, 0);
                }
                for (k = 0; (unsigned int)k < extset->number; k++) {
                    if (lyp_deviate_apply_ext(dev, target, LYEXT_SUBSTMT_SELF, (struct lys_ext *)extset->set.g[k])) {
                        ly_set_free(extset);
                        return EXIT_FAILURE;
                    }
                }
                ly_set_free(extset);
            }


            if (dev->unique_size && lyp_deviate_apply_ext(dev, target, LYEXT_SUBSTMT_UNIQUE, NULL)) {
                return EXIT_FAILURE;
            }

            if (dev->units && lyp_deviate_apply_ext(dev, target, LYEXT_SUBSTMT_UNITS, NULL)) {
                return EXIT_FAILURE;
            }

            if (dev->dflt_size && lyp_deviate_apply_ext(dev, target, LYEXT_SUBSTMT_DEFAULT, NULL)) {
                return EXIT_FAILURE;
            }

            if ((dev->flags & LYS_CONFIG_MASK) && lyp_deviate_apply_ext(dev, target, LYEXT_SUBSTMT_CONFIG, NULL)) {
                return EXIT_FAILURE;
            }

            if ((dev->flags & LYS_MAND_MASK) && lyp_deviate_apply_ext(dev, target, LYEXT_SUBSTMT_MANDATORY, NULL)) {
                return EXIT_FAILURE;
            }

            if (dev->min_set && lyp_deviate_apply_ext(dev, target, LYEXT_SUBSTMT_MIN, NULL)) {
                return EXIT_FAILURE;
            }
            if (dev->min_set && lyp_deviate_apply_ext(dev, target, LYEXT_SUBSTMT_MAX, NULL)) {
                return EXIT_FAILURE;
            }

        }
    }

    return EXIT_SUCCESS;
}
