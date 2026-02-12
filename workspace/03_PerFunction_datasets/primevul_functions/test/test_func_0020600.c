status_put_font(stream * s, pcl_state_t * pcs,
                uint font_id, uint internal_id,
                pl_font_t * plfont, int font_set, bool extended)
{
    char paren = (font_set > 0 ? ')' : '(');
    bool proportional = plfont->params.proportional_spacing;


    stputs(s, "SELECT=\"");
    if (pl_font_is_bound(plfont) || font_set > 0) {

        uint symbol_set = font_set > 0 ?
            pcs->font_selection[font_set].params.symbol_set :
            plfont->params.symbol_set;
        stprintf(s, "<Esc>%c%u%c", paren, symbol_set >> 5,
                 (symbol_set & 31) + 'A' - 1);
    }


    stprintf(s, "<Esc>%cs%dp", paren, proportional);
    if (plfont->scaling_technology == plfst_bitmap) {
        status_put_floating(s, pl_fp_pitch_per_inch(&plfont->params));
        stputs(s, "h");
        status_put_floating(s, plfont->params.height_4ths / 4.0);
        stputs(s, "v");
    } else {

        if (font_set > 0) {


            if (proportional) {
                status_put_floating(s,
                                    pcs->font_selection[font_set].params.
                                    height_4ths / 4.0);
                stputs(s, "h");
            } else {
                status_put_floating(s,
                                    pl_fp_pitch_per_inch(&pcs->
                                                         font_selection
                                                         [font_set].params));
                stputs(s, "v");
            }
        } else {
            stputs(s, proportional ? "__v" : "__h");
        }
    }
    stprintf(s, "%ds%db%uT", plfont->params.style,
             plfont->params.stroke_weight, plfont->params.typeface_family);
    if (plfont->storage & pcds_downloaded)
        stprintf(s, "<Esc>%c%uX", paren, font_id);
    stputs(s, "\"\r\n");
    if (!pl_font_is_bound(plfont) && font_set < 0) {
        int nid;
        ushort *idlist;
        pl_dict_enum_t denum;
        gs_const_string key;
        void *value;

        idlist = (ushort *) gs_alloc_bytes(pcs->memory,
                                           pl_dict_length(&pcs->
                                                          soft_symbol_sets,
                                                          false) +
                                           pl_dict_length(&pcs->
                                                          built_in_symbol_sets,
                                                          false),
                                           "status_fonts(idlist)");
        if (idlist == NULL)
            return e_Memory;
        nid = 0;


        pl_dict_set_parent(&pcs->soft_symbol_sets,
                           &pcs->built_in_symbol_sets);
        pl_dict_enum_begin(&pcs->soft_symbol_sets, &denum);
        while (pl_dict_enum_next(&denum, &key, &value)) {
            pcl_symbol_set_t *ssp = (pcl_symbol_set_t *) value;
            pl_glyph_vocabulary_t gx;

            for (gx = plgv_MSL; gx < plgv_next; gx++)
                if (ssp->maps[gx] != NULL &&
                    pcl_check_symbol_support(ssp->maps[gx]->
                                             character_requirements,
                                             plfont->character_complement)) {
                    nid =
                        status_add_symbol_id(idlist, nid,
                                             (ssp->maps[gx]->id[0] << 8) +
                                             ssp->maps[gx]->id[1]);
                    break;
                }
        }
        pl_dict_set_parent(&pcs->soft_symbol_sets, NULL);


        gs_free_object(pcs->memory, (void *)idlist, "status_fonts(idlist)");
    }
    if (extended) {
        if (plfont->storage & pcds_temporary)
            stputs(s, "DEFID=NONE\r\n");
        else {
            stputs(s, "DEFID=\"");
            if (plfont->storage & pcds_all_cartridges) {
                int c;
                int n = (plfont->storage & pcds_all_cartridges) >>
                    pcds_cartridge_shift;


                for (c = 0; (n & 1) == 0; c++)
                    n >>= 1;
                stprintf(s, "C%d ", c);
            } else if (plfont->storage & pcds_all_simms) {
                int m;
                int n = (plfont->storage & pcds_all_simms) >> pcds_simm_shift;


                for (m = 0; (n & 1) == 0; m++)
                    n >>= 1;
                stprintf(s, "M%d ", m);
            } else

                stputs(s, (plfont->storage & pcds_internal) ? "I " : "S ");
            stprintf(s, "%d\"\r\n", internal_id);
        }


        if ((plfont->storage & pcds_downloaded) && plfont->header != NULL) {


            pcl_font_header_t *hdr = (pcl_font_header_t *) (plfont->header);

            stprintf(s, "NAME=\"%.16s\"\r\n", hdr->FontName);
        }
    }
    return 0;
}
