applyConfig(){
    if(GLOBAL(lcdcontrast)>0)
        lcdSetContrast(GLOBAL(lcdcontrast));
    if(GLOBAL(develmode))
        enableConfig(CFG_TYPE_DEVEL,1);
    if(isNight())
        backlightSetBrightness(GLOBAL(lcdbacklight));
}
