#include "Stretch_Option.h"

bool is_number2(char expr[]){

    int i=0,count_decimals=0;
    if(expr[0]=='\0'){return false;}
    while(expr[i]!='\0'){
        if(expr[i]=='.'){if(count_decimals++>0){return false;}}
        else if(!(expr[i]>='0'&&expr[i]<='9')){return false;}
        i++;
        if(i>=10){return false;}
    }
    return true;
}
void copy_string2(char s1[],Glib::ustring s2){
    int i=0;
    for(;s2[i]!='\0';)
    {
        if(i==14){break;}
        s1[i]=s2[i];
        i++;
    }
    s1[i]='\0';
    return;
}



Stretch_Option::Stretch_Option()
{
    //ctor

    FILE*stretch_coordinates=fopen("Program_Files/Temp_Files/stretch_coordinates","wb+");
    float x1=-1,y1=-1;
    if(stretch_coordinates!=NULL){
        fwrite(&x1,sizeof(x1),1,stretch_coordinates);
        fwrite(&y1,sizeof(y1),1,stretch_coordinates);
        fclose(stretch_coordinates);
    }
    set_position(Gtk::WIN_POS_CENTER);

    set_default_size(400, 200);
    set_title("Enter Coefficients for Stretching");

    Gtk::Box *vbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0));
    add(*vbox);

    Gtk::Grid *grid = Gtk::manage(new Gtk::Grid);
    grid->set_border_width(10);
    grid->set_row_spacing(10);
    grid->set_column_spacing(30);
    vbox->add(*grid);

    Gtk::Label *l_1 = Gtk::manage(new Gtk::Label("Enter the Final Image Height :  "));
    grid->attach(*l_1, 0, 0, 1, 1);

    Gtk::Label *l_x1 = Gtk::manage(new Gtk::Label("(as a coefficient of present Height)"));
    grid->attach(*l_x1, 0, 1, 1, 1);


    Gtk::Entry *e_x1 = Gtk::manage(new Gtk::Entry());
    e_x1->set_hexpand(true);
    grid->attach(*e_x1, 1, 0, 2, 1);

    Gtk::Label *l_2 = Gtk::manage(new Gtk::Label("Enter the Final Image Width :  "));
    grid->attach(*l_2, 0, 3, 1, 1);

    Gtk::Label *l_3 = Gtk::manage(new Gtk::Label(" "));
    grid->attach(*l_3, 0, 2, 1, 1);

    Gtk::Label *l_x2 = Gtk::manage(new Gtk::Label("(as a coefficient of present Width)"));
    grid->attach(*l_x2, 0, 4, 1, 1);


    Gtk::Entry *e_y1 = Gtk::manage(new Gtk::Entry());
    e_y1->set_hexpand(true);
    grid->attach(*e_y1, 1, 3, 2, 1);

    show_all_children();


    Gtk::Button *bstretch = Gtk::manage(new Gtk::Button("Stretch"));
    bstretch->signal_clicked().connect(sigc::bind<Gtk::Entry*, Gtk::Entry*>(sigc::mem_fun(*this, &Stretch_Option::on_stretch_click), e_x1,e_y1));
    grid->attach(*bstretch, 2, 5, 1, 1);


    vbox->show_all();
}

void Stretch_Option::on_stretch_click(Gtk::Entry *e_x1,Gtk::Entry *e_y1){
    float x1=0,y1=0;
    char s_x1[15],s_y1[15];
    copy_string2(s_x1,e_x1->get_text());
    copy_string2(s_y1,e_y1->get_text());
    if(!is_number2(s_x1)||!is_number2(s_y1)){
        dialog("Please Enter Valid Numbers!");
    }
    else{

        sscanf(s_x1,"%f",&x1);
        sscanf(s_y1,"%f",&y1);

        if((x1<0||x1>5)||(y1<0||y1>5)){dialog("Please Enter Valid Numbers between 0 and 5");}
        else{

            FILE*stretch_coordinates=fopen("Program_Files/Temp_Files/stretch_coordinates","wb+");
            if(stretch_coordinates==NULL){dialog("Sorry! Unable to Stretch Image.");}
            else{
                fwrite(&x1,sizeof(x1),1,stretch_coordinates);
                fwrite(&y1,sizeof(y1),1,stretch_coordinates);
                fclose(stretch_coordinates);

            }

            hide();
            }

    }

};



Stretch_Option::~Stretch_Option()
{
    //dtor
}

void Stretch_Option::dialog(Glib::ustring msg)
{
    Gtk::MessageDialog dlg(msg, false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
    dlg.set_title("Digital Image Processor");
    dlg.run();
}

