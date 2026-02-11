HSP_Display_get_ruler_char(HSP_Display *hd, gint pos,
                                       gint advance){
    register gint stop;
    register gint pad_length = 3;
    stop = hd->padding * hd->max_advance;
    if(pos >= stop){
        if(pos < (stop+pad_length)){
            return '#';
            }
        stop = ((hd->padding+hd->hsp->length) * hd->max_advance)
             + pad_length;
        if(pos >= stop){
            if(pos < (stop+pad_length)){
                return '#';
                }
            pos -= pad_length;
            }
        pos -= pad_length;
        }
    if((pos/advance) & 1)
        return '=';
    return '-';
    }
