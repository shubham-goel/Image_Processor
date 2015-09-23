#include "Enter_Hue.h"


bool is_number5(char expr[]){

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
void copy_string5(char s1[],Glib::ustring s2){
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



Enter_Hue::Enter_Hue()
{
    //ctor
    float x1=-1;
    set_position(Gtk::WIN_POS_CENTER);
    FILE*rotate_Hue=fopen("Program_Files/Temp_Files/Rotate_Hue","wb+");
    if(rotate_Hue!=NULL){
        fwrite(&x1,sizeof(x1),1,rotate_Hue);
        fclose(rotate_Hue);
    }

    set_default_size(400, 200);
    set_title("Enter Hue Value");

    Gtk::Box *vbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0));
    add(*vbox);

    Gtk::Grid *grid = Gtk::manage(new Gtk::Grid);
    grid->set_border_width(10);
    grid->set_row_spacing(5);
    vbox->add(*grid);

    Gtk::Label *lHue = Gtk::manage(new Gtk::Label("Enter a Hue between 0 and 360: "));
    grid->attach(*lHue, 0, 0, 1, 1);

    Gtk::Entry *eHue = Gtk::manage(new Gtk::Entry());
    eHue->set_hexpand(true);
    grid->attach(*eHue, 1, 0, 2, 1);
    show_all_children();

    Gtk::Button *bopen = Gtk::manage(new Gtk::Button("Change Hue"));
    bopen->signal_clicked().connect(sigc::bind<Gtk::Entry*>(sigc::mem_fun(*this, &Enter_Hue::on_hue_click), eHue));
    grid->attach(*bopen, 2, 2, 1, 1);


    Gtk::Image*hue_chart=Gtk::manage(new Gtk::Image);
    hue_chart->set("Program_Files/hsl_top.JPG");
    grid->attach(*hue_chart,0,2,2,1);


    vbox->show_all();
}

void Enter_Hue::on_hue_click(Gtk::Entry *eHue){

    float x1=0;
    char s_x1[15];
    copy_string5(s_x1,eHue->get_text());
    if(!is_number5(s_x1)){
        dialog("Please Enter Valid Hue Value!");
    }
    else{
        sscanf(s_x1,"%f",&x1);

        if((x1<0||x1>360)){dialog("Please Enter Valid Hue!");}
        else{

            FILE*rotate_Hue=fopen("Program_Files/Temp_Files/Rotate_Hue","wb+");
            if(rotate_Hue==NULL){dialog("Sorry! Unable to change Hue.");}
            else{
                fwrite(&x1,sizeof(x1),1,rotate_Hue);
                fclose(rotate_Hue);
            }
            hide();
            }

    }

};

Enter_Hue::~Enter_Hue()
{
    //dtor
}

void Enter_Hue::dialog(Glib::ustring msg)
{
    Gtk::MessageDialog dlg(msg, false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
    dlg.set_title("Digital Image Processor");
    dlg.run();
}
