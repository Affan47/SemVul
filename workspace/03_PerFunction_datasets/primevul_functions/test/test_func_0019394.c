static int formparse(struct Configurable *config,
                     char *input,
                     struct curl_httppost **httppost,
                     struct curl_httppost **last_post,
                     bool literal_value)
{


  char name[256];
  char *contents;
  char major[128];
  char minor[128];
  char *contp;
  const char *type = NULL;
  char *sep;
  char *sep2;

  if((1 == sscanf(input, "%255[^=]=", name)) &&
     (contp = strchr(input, '='))) {


    contents = strdup(contp+1);
    if(!contents) {
      fprintf(stderr, "out of memory\n");
      return 1;
    }
    contp = contents;

    if('@' == contp[0] && !literal_value) {
      struct multi_files *multi_start = NULL, *multi_current = NULL;

      contp++;

      multi_start = multi_current=NULL;

      do {


        char *ptr;
        char *filename=NULL;

        sep=strchr(contp, FORM_TYPE_SEPARATOR);
        sep2=strchr(contp, FORM_FILE_SEPARATOR);


        if(sep2 && (sep2 < sep)) {
          sep = sep2;


        }

        type = NULL;

        if(sep) {


          if(FORM_FILE_SEPARATOR == *sep)
            ptr = NULL;
          else
            ptr = sep+1;

          *sep=0;

          while(ptr && (FORM_FILE_SEPARATOR!= *ptr)) {


            while(ISSPACE(*ptr))
              ptr++;

            if(curlx_strnequal("type=", ptr, 5)) {

              type = &ptr[5];


              if(2 != sscanf(type, "%127[^/]/%127[^;,\n]",
                             major, minor)) {
                warnf(config, "Illegally formatted content-type field!\n");
                free(contents);
                FreeMultiInfo (multi_start);
                return 2;
              }

              sep = (char *)type + strlen(major)+strlen(minor)+1;

              if(*sep) {
                *sep=0;

                ptr=sep+1;
              }
              else
                ptr = NULL;
            }
            else if(curlx_strnequal("filename=", ptr, 9)) {
              filename = &ptr[9];
              ptr=strchr(filename, FORM_TYPE_SEPARATOR);
              if(!ptr) {
                ptr=strchr(filename, FORM_FILE_SEPARATOR);
              }
              if(ptr) {
                *ptr=0;
                ptr++;
              }
            }
            else

              break;
          }

          if(ptr)
            sep=strchr(ptr, FORM_FILE_SEPARATOR);
          else
            sep=NULL;
        }
        else {
          sep=strchr(contp, FORM_FILE_SEPARATOR);
        }
        if(sep) {

          *sep =0;
          sep++;
        }


        if (!AddMultiFiles (contp, type, filename, &multi_start,
                            &multi_current)) {
          warnf(config, "Error building form post!\n");
          free(contents);
          FreeMultiInfo (multi_start);
          return 3;
        }
        contp = sep;

      } while(sep && *sep);


      if (multi_start) {
        struct curl_forms *forms = NULL;
        struct multi_files *ptr = multi_start;
        unsigned int i, count = 0;
        while (ptr) {
          ptr = ptr->next;
          ++count;
        }
        forms =
          (struct curl_forms *)malloc((count+1)*sizeof(struct curl_forms));
        if (!forms)
        {
          fprintf(stderr, "Error building form post!\n");
          free(contents);
          FreeMultiInfo (multi_start);
          return 4;
        }
        for (i = 0, ptr = multi_start; i < count; ++i, ptr = ptr->next)
        {
          forms[i].option = ptr->form.option;
          forms[i].value = ptr->form.value;
        }
        forms[count].option = CURLFORM_END;
        FreeMultiInfo (multi_start);
        if (curl_formadd(httppost, last_post,
                         CURLFORM_COPYNAME, name,
                         CURLFORM_ARRAY, forms, CURLFORM_END) != 0) {
          warnf(config, "curl_formadd failed!\n");
          free(forms);
          free(contents);
          return 5;
        }
        free(forms);
      }
    }
    else {
      struct curl_forms info[4];
      int i = 0;
      char *ct = literal_value? NULL: strstr(contp, ";type=");

      info[i].option = CURLFORM_COPYNAME;
      info[i].value = name;
      i++;

      if(ct) {
        info[i].option = CURLFORM_CONTENTTYPE;
        info[i].value = &ct[6];
        i++;
        ct[0]=0;
      }

      if( contp[0]=='<' && !literal_value) {
        info[i].option = CURLFORM_FILECONTENT;
        info[i].value = contp+1;
        i++;
        info[i].option = CURLFORM_END;

        if (curl_formadd(httppost, last_post,
                         CURLFORM_ARRAY, info, CURLFORM_END ) != 0) {
          warnf(config, "curl_formadd failed, possibly the file %s is bad!\n",
                contp+1);
          free(contents);
          return 6;
        }
      }
      else {
#ifdef CURL_DOES_CONVERSIONS
        convert_to_network(contp, strlen(contp));
#endif
        info[i].option = CURLFORM_COPYCONTENTS;
        info[i].value = contp;
        i++;
        info[i].option = CURLFORM_END;
        if (curl_formadd(httppost, last_post,
                         CURLFORM_ARRAY, info, CURLFORM_END) != 0) {
          warnf(config, "curl_formadd failed!\n");
          free(contents);
          return 7;
        }
      }
    }

  }
  else {
    warnf(config, "Illegally formatted input field!\n");
    return 1;
  }
  free(contents);
  return 0;
}
