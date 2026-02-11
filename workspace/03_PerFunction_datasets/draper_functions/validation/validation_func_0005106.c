_evas_textblock_cursor_range_text_plain_get(const Evas_Textblock_Cursor *cur1, const Evas_Textblock_Cursor *_cur2)
{
   Eina_UStrbuf *buf;
   Evas_Object_Textblock_Node_Text *n1, *n2;
   Evas_Textblock_Cursor *cur2;

   buf = eina_ustrbuf_new();

   if (!cur1 || !cur1->node) return NULL;
   if (!_cur2 || !_cur2->node) return NULL;
   if (cur1->obj != _cur2->obj) return NULL;
   if (evas_textblock_cursor_compare(cur1, _cur2) > 0)
     {
	const Evas_Textblock_Cursor *tc;

	tc = cur1;
	cur1 = _cur2;
	_cur2 = tc;
     }
   n1 = cur1->node;
   n2 = _cur2->node;

   cur2 = alloca(sizeof(Evas_Textblock_Cursor));
   cur2->obj = _cur2->obj;
   evas_textblock_cursor_copy(_cur2, cur2);


   if (n1 == n2)
     {
        const Eina_Unicode *tmp;
        tmp = eina_ustrbuf_string_get(n1->unicode);
        eina_ustrbuf_append_length(buf, tmp + cur1->pos, cur2->pos - cur1->pos);
     }
   else
     {
        const Eina_Unicode *tmp;
        tmp = eina_ustrbuf_string_get(n1->unicode);
        eina_ustrbuf_append(buf, tmp + cur1->pos);
        n1 = _NODE_TEXT(EINA_INLIST_GET(n1)->next);
        while (n1 != n2)
          {
             tmp = eina_ustrbuf_string_get(n1->unicode);
             eina_ustrbuf_append_length(buf, tmp,
                   eina_ustrbuf_length_get(n1->unicode));
             n1 = _NODE_TEXT(EINA_INLIST_GET(n1)->next);
          }
        tmp = eina_ustrbuf_string_get(n2->unicode);
        eina_ustrbuf_append_length(buf, tmp, cur2->pos);
     }


     {
        char *ret;
        ret = eina_unicode_unicode_to_utf8(eina_ustrbuf_string_get(buf), NULL);
        eina_ustrbuf_free(buf);
        return ret;
     }
}
