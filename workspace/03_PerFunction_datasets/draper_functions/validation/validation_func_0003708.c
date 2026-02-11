destroy() {
  Cuyo::destroy();

  delete mBlattMenu;
  delete mBlattSpiel;

  Punktefeld::destroy();
  Blatt::destroyBlaetter();
  Sound::destroy();
  Font::destroy();
  Area::destroy();

  Bilddatei::destroy();
}
