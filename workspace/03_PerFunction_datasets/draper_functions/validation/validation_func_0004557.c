Window_draw_slider(T_Scroller_button * button)
{
  word slider_position;

  if (button->Is_horizontal)
  {
    slider_position=button->Pos_X+12;

    Window_rectangle(slider_position,
          button->Pos_Y,
          button->Length-24,11,MC_Black);

    if (button->Nb_elements>button->Nb_visibles)
      slider_position+=
        ((button->Length-24-button->Cursor_length)*(button->Position)+(button->Nb_elements-button->Nb_visibles)/2)/(button->Nb_elements-button->Nb_visibles);

    Window_rectangle(slider_position,
          button->Pos_Y,
          button->Cursor_length,11,MC_OnBlack);

    Update_window_area(button->Pos_X,
          button->Pos_Y,
          button->Length,11);
  }
  else
  {
    slider_position=button->Pos_Y+12;

    Window_rectangle(button->Pos_X,
          slider_position,
          11,button->Length-24,MC_Black);

    if (button->Nb_elements>button->Nb_visibles)
      slider_position+=
        ((button->Length-24-button->Cursor_length)*(button->Position)+(button->Nb_elements-button->Nb_visibles)/2)/(button->Nb_elements-button->Nb_visibles);


    Window_rectangle(button->Pos_X,
          slider_position,
          11,button->Cursor_length,MC_OnBlack);

    Update_window_area(button->Pos_X,
          button->Pos_Y,
          11,button->Length);
  }
}
