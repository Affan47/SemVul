text(const char* txt, boolean update) {

   text_editor_->Select(0);
   text_editor_->DeleteText(te_buffer_->characters());


   te_buffer_->Insert(0, txt, strlen(txt));
   text_editor_->Edit(te_buffer_, 0);
   text_editor_->BeginningOfText();

   start_row_= 0;
   if (update)
       line_update();
}
