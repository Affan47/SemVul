zzip_get_default_ext(void)
{
    static zzip_strings_t ext[] = {

       ".zip", ".ZIP",
#     ifdef ZZIP_USE_ZIPLIKES
       ".pk3", ".PK3",
       ".jar", ".JAR",
#      endif

        0
    };

    return ext;
}
