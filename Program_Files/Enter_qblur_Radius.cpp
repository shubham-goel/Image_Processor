#include "Enter_qblur_Radius.h"

bool is_number6(char expr[]){

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
void copy_string6(char s1[],Glib::ustring s2){
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

Enter_qblur_Radius::Enter_qblur_Radius()
{
    //ctor
    set_position(Gtk::WIN_POS_CENTER);
    FILE*qblur_coordinates=fopen("Program_Files/Temp_Files/qblur_coordinates","wb+");
    float x1=-1;
    if(qblur_coordinates!=NULL){
        fwrite(&x1,sizeof(x1),1,qblur_coordinates);
        fclose(qblur_coordinates);
    }


    set_default_size(400, 200);
    set_title("Blurring Extent");

    set_urgency_hint(true);

    Gtk::Box *vbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0));
    add(*vbox);

    Gtk::Grid *grid = Gtk::manage(new Gtk::Grid);
    grid->set_border_width(10);
    grid->set_row_spacing(10);
    grid->set_column_spacing(30);
    vbox->add(*grid);

    Gtk::Label *l_1 = Gtk::manage(new Gtk::Label("Enter the Extent of Blurring  "));
    grid->attach(*l_1, 0, 0, 1, 1);

    Gtk::Label *l_x1 = Gtk::manage(new Gtk::Label("(A number on the scale of 1-20)"));
    grid->attach(*l_x1, 0, 1, 1, 1);


    Gtk::Entry *e_x1 = Gtk::manage(new Gtk::Entry());
    e_x1->set_hexpand(true);
    grid->attach(*e_x1, 1, 0, 2, 1);


    show_all_children();


    Gtk::Button *bqblur = Gtk::manage(new Gtk::Button("Quick Blur"));
    bqblur->signal_clicked().connect(sigc::bind<Gtk::Entry*>(sigc::mem_fun(*this, &Enter_qblur_Radius::on_qblur_click), e_x1));
//    bcrop->signal_clicked().connect(sigc::mem_fun(*this, &Enter_Crop_Coordinates::on_crop_click));
    grid->attach(*bqblur, 2, 2, 1, 1);


    vbox->show_all();
}

void Enter_qblur_Radius::on_qblur_click(Gtk::Entry *e_x1){
    float x1=0;
    char s_x1[15];
    copy_string6(s_x1,e_x1->get_text());
    if(!is_number6(s_x1)){
        dialog("Please Enter a Valid Number!");
    }
    else{

        sscanf(s_x1,"%f",&x1);

        if((x1<0||x1>20)){dialog("Please Enter a Valid Number between 0 and 20");}
        else{

            FILE*stretch_coordinates=fopen("Program_Files/Temp_Files/qblur_coordinates","wb+");
            if(stretch_coordinates==NULL){dialog("Sorry! Unable to qblur Image.");hide();return;}
            else{
                fwrite(&x1,sizeof(x1),1,stretch_coordinates);
                fclose(stretch_coordinates);
            }

            hide();
            }

    }
    return;
}

Enter_qblur_Radius::~Enter_qblur_Radius()
{
    //dtor
}

void Enter_qblur_Radius::dialog(Glib::ustring msg)
{
    Gtk::MessageDialog dlg(msg, false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
    dlg.set_title("Digital Image Processor");
    dlg.run();
}
