jp_delete_record(const char *DB_name, buf_rec *br, int flag)
{
   FILE *pc_in;
   PC3RecordHeader header;
   char PC_name[FILENAME_MAX];

   if (br==NULL) {
      return EXIT_FAILURE;
   }

   g_snprintf(PC_name, sizeof(PC_name), "%s.pc3", DB_name);

   if ((br->rt==DELETED_PALM_REC) || (br->rt==MODIFIED_PALM_REC)) {
      jp_logf(JP_LOG_INFO, _("This record is already deleted.\n"
                  "It is scheduled to be deleted from the Palm on the next sync.\n"));
      return EXIT_SUCCESS;
   }
   switch (br->rt) {
    case NEW_PC_REC:
    case REPLACEMENT_PALM_REC:
      pc_in=jp_open_home_file(PC_name, "r+");
      if (pc_in==NULL) {
         jp_logf(JP_LOG_WARN, _("Unable to open PC records file\n"));
         return EXIT_FAILURE;
      }
      while(!feof(pc_in)) {
         read_header(pc_in, &header);
         if (feof(pc_in)) {
            jp_logf(JP_LOG_WARN, _("Couldn't find record to delete\n"));
            jp_close_home_file(pc_in);
            return EXIT_FAILURE;
         }
         if (header.header_version==2) {

            if ((header.unique_id==br->unique_id) &&
               ((header.rt==NEW_PC_REC) || (header.rt==REPLACEMENT_PALM_REC))) {
               if (fseek(pc_in, -header.header_len, SEEK_CUR)) {
                  jp_logf(JP_LOG_WARN, "fseek failed\n");
               }
               header.rt=DELETED_PC_REC;
               write_header(pc_in, &header);
               jp_logf(JP_LOG_DEBUG, "record deleted\n");
               jp_close_home_file(pc_in);
               return EXIT_SUCCESS;
            }
         } else {
            jp_logf(JP_LOG_WARN, _("Unknown header version %d\n"), header.header_version);
         }
         if (fseek(pc_in, header.rec_len, SEEK_CUR)) {
            jp_logf(JP_LOG_WARN, "fseek failed\n");
         }
      }
      jp_close_home_file(pc_in);
      return EXIT_FAILURE;

    case PALM_REC:
      jp_logf(JP_LOG_DEBUG, "Deleting Palm ID %d\n", br->unique_id);
      pc_in=jp_open_home_file(PC_name, "a");
      if (pc_in==NULL) {
         jp_logf(JP_LOG_WARN, _("Unable to open PC records file\n"));
         return EXIT_FAILURE;
      }
      header.unique_id=br->unique_id;
      if (flag==MODIFY_FLAG) {
         header.rt=MODIFIED_PALM_REC;
      } else {
         header.rt=DELETED_PALM_REC;
      }
      header.attrib=br->attrib;
      header.rec_len=br->size;

      jp_logf(JP_LOG_DEBUG, "writing header to pc file\n");
      write_header(pc_in, &header);


      jp_logf(JP_LOG_DEBUG, "writing record to pc file, %d bytes\n", header.rec_len);
      fwrite(br->buf, header.rec_len, 1, pc_in);
      jp_logf(JP_LOG_DEBUG, "record deleted\n");
      jp_close_home_file(pc_in);
      break;
    default:
      break;
   }

   return EXIT_SUCCESS;
}
