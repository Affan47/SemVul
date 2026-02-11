e_entry_text_set(Evas_Object *entry, const char *_text)
{
   E_Entry_Smart_Data *sd;
   char *text = NULL;
   const char *otext;

   if (evas_object_smart_smart_get(entry) != _e_entry_smart) SMARTERRNR();
   if ((!entry) || (!(sd = evas_object_smart_data_get(entry))))
     return;

   text = evas_textblock_text_utf8_to_markup(
         edje_object_part_object_get(sd->entry_object, ENTRY_PART_NAME),
         _text);
   otext = edje_object_part_text_get(sd->entry_object, ENTRY_PART_NAME);
   if ((text) && (otext) && (!strcmp(text, otext)))
     {
        free(text);
        return;
     }
   if ((!text) && (!otext)) return;
   edje_object_part_text_set(sd->entry_object, ENTRY_PART_NAME, text);
   sd->changing++;
   edje_object_message_signal_process(sd->entry_object);
   sd->changing--;
   evas_object_smart_callback_call(entry, "changed", NULL);
   free(text);
}
