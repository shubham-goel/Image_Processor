#include "Enter_Angle.h"


bool is_number1(char expr[]){

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
void copy_string1(char s1[],Glib::ustring s2){
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



Enter_Angle::Enter_Angle()
{
    //ctor
    float x1=-1;
    set_position(Gtk::WIN_POS_CENTER);
    FILE*rotate_angle=fopen("Program_Files/Temp_Files/Rotate_Angle","wb+");
    if(rotate_angle!=NULL){
        fwrite(&x1,sizeof(x1),1,rotate_angle);
        fclose(rotate_angle);
    }

    set_default_size(400, 200);
    set_title("Rotate Anti-Clockwise");

    Gtk::Box *vbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0));
    add(*vbox);

    Gtk::Grid *grid = Gtk::manage(new Gtk::Grid);
    grid->set_border_width(10);
    grid->set_row_spacing(5);
    vbox->add(*grid);

    Gtk::Label *langle = Gtk::manage(new Gtk::Label("Enter an Angle between 0 and 360: "));
    grid->attach(*langle, 0, 0, 1, 1);

    Gtk::Entry *eangle = Gtk::manage(new Gtk::Entry());
    eangle->set_hexpand(true);
    grid->attach(*eangle, 1, 0, 2, 1);
    show_all_children();

    Gtk::Button *bopen = Gtk::manage(new Gtk::Button("Rotate"));
    bopen->signal_clicked().connect(sigc::bind<Gtk::Entry*>(sigc::mem_fun(*this, &Enter_Angle::on_rotate_click), eangle));
    grid->attach(*bopen, 2, 2, 1, 1);


    vbox->show_all();
}

void Enter_Angle::on_rotate_click(Gtk::Entry *eangle){

    float x1=0;
    char s_x1[15];
    copy_string1(s_x1,eangle->get_text());
    if(!is_number1(s_x1)){
        dialog("Please Enter Valid Angle!");
    }
    else{
        sscanf(s_x1,"%f",&x1);


        if((x1<=0||x1>=360)){dialog("Please Enter Valid Angle!");}
        else{

            FILE*rotate_angle=fopen("Program_Files/Temp_Files/Rotate_Angle","wb+");
            if(rotate_angle==NULL){dialog("Sorry! Unable to Rotate Image.");}
            else{
                fwrite(&x1,sizeof(x1),1,rotate_angle);
                fclose(rotate_angle);
            }
            hide();
            }

    }

};

Enter_Angle::~Enter_Angle()
{
    //dtor
}

void Enter_Angle::dialog(Glib::ustring msg)
{
    Gtk::MessageDialog dlg(msg, false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
    dlg.set_title("Digital Image Processor");
    dlg.run();
}
