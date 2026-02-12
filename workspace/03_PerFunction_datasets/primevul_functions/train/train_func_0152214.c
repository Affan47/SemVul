static void copy_options(struct Sass_Options* to, struct Sass_Options* from) {

    if (to == from) return;

    sass_clear_options(to);

    *to = *from;

    sass_reset_options(from);
  }
