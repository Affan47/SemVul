static void printCSS(FILE *f)
{


  static const char css[] =
    "<style type=\"text/css\">" "\n"
    "<!--" "\n"
    ".xflip {" "\n"
    "    -moz-transform: scaleX(-1);" "\n"
    "    -webkit-transform: scaleX(-1);" "\n"
    "    -o-transform: scaleX(-1);" "\n"
    "    transform: scaleX(-1);" "\n"
    "    filter: fliph;" "\n"
    "}" "\n"
    ".yflip {" "\n"
    "    -moz-transform: scaleY(-1);" "\n"
    "    -webkit-transform: scaleY(-1);" "\n"
    "    -o-transform: scaleY(-1);" "\n"
    "    transform: scaleY(-1);" "\n"
    "    filter: flipv;" "\n"
    "}" "\n"
    ".xyflip {" "\n"
    "    -moz-transform: scaleX(-1) scaleY(-1);" "\n"
    "    -webkit-transform: scaleX(-1) scaleY(-1);" "\n"
    "    -o-transform: scaleX(-1) scaleY(-1);" "\n"
    "    transform: scaleX(-1) scaleY(-1);" "\n"
    "    filter: fliph + flipv;" "\n"
    "}" "\n"
    "-->" "\n"
    "</style>" "\n";

  fwrite( css, sizeof(css)-1, 1, f );
}
