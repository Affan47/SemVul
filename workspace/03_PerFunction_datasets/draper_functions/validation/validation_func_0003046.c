TaskWidget( PG_Widget* parent, const PG_Point& pos, int width, Command* command, GameMap* map, TaskContainer* taskContainer )
   : ActionWidget( parent,pos, width, *command, map ) , gamemap( map )
      {
         this->taskContainer = taskContainer;
         this->command = command;

         (new PG_Button(this, PG_Rect( width-70, 5, 60, 15 ), "Run"))->sigClick.connect( SigC::slot( *this, &TaskWidget::run ));
         (new PG_Button(this, PG_Rect( width-70, 22, 60, 15 ), "Cancel"))->sigClick.connect( SigC::slot( *this, &TaskWidget::cancel ));
      }
