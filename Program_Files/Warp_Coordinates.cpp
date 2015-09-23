#include "Warp_Coordinates.h"
#include<iostream>
bool is_number4(char expr[]){

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
void copy_string4(char s1[],Glib::ustring s2){
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
void swap_numbers4(float&a,float&b){
    float temp=a;
    a=b;
    b=temp;
    return;
}

Warp_Coordinates::Warp_Coordinates()
{
    //ctor
    float x1=-1,y1=-1,x2=-1,y2=-1;
    FILE*warp_coordinates_1=fopen("Program_Files/Temp_Files/warp_Coordinates_1","wb+");
    if(warp_coordinates_1==NULL){dialog("Sorry! Unable to Warp Image.");}
    else{
        fwrite(&x1,sizeof(x1),1,warp_coordinates_1);
        fwrite(&y1,sizeof(y1),1,warp_coordinates_1);
        fwrite(&x2,sizeof(x2),1,warp_coordinates_1);
        fwrite(&y2,sizeof(y2),1,warp_coordinates_1);
        fclose(warp_coordinates_1);
    }

    FILE*warp_coordinates_2=fopen("Program_Files/Temp_Files/warp_Coordinates_2","wb+");
    if(warp_coordinates_2==NULL){dialog("Sorry! Unable to Warp Image.");}
    else{
        fwrite(&x1,sizeof(x1),1,warp_coordinates_2);
        fwrite(&y1,sizeof(y1),1,warp_coordinates_2);
        fwrite(&x2,sizeof(x2),1,warp_coordinates_2);
        fwrite(&y2,sizeof(y2),1,warp_coordinates_2);
        fclose(warp_coordinates_2);
    }

    set_default_size(400, 200);
    set_title("Enter Warp Coordinates");
    set_position(Gtk::WIN_POS_CENTER);

    Gtk::Box *vbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0));
    add(*vbox);

    Gtk::Grid *grid = Gtk::manage(new Gtk::Grid);
    grid->set_border_width(10);
    grid->set_row_spacing(5);
    vbox->add(*grid);

    Gtk::Label *l_1 = Gtk::manage(new Gtk::Label("Enter Coordinates of Top-Left Corner  "));
    grid->attach(*l_1, 0, 0, 1, 1);

    Gtk::Label *l_x1 = Gtk::manage(new Gtk::Label("X: "));
    grid->attach(*l_x1, 1, 0, 1, 1);


    Gtk::Entry *e_x1 = Gtk::manage(new Gtk::Entry());
    e_x1->set_hexpand(true);
    grid->attach(*e_x1, 2, 0, 2, 1);

    Gtk::Label *l_y1 = Gtk::manage(new Gtk::Label("Y: "));
    grid->attach(*l_y1, 1, 1, 1, 1);

    Gtk::Entry *e_y1 = Gtk::manage(new Gtk::Entry());
    e_y1->set_hexpand(true);
    grid->attach(*e_y1, 2, 1, 2, 1);

    Gtk::Label *l_2 = Gtk::manage(new Gtk::Label("Enter Coordinates of Top-Right Corner  "));
    grid->attach(*l_2, 0, 2, 1, 1);

    Gtk::Label *l_x2 = Gtk::manage(new Gtk::Label("X: "));
    grid->attach(*l_x2, 1, 2, 1, 1);


    Gtk::Entry *e_x2 = Gtk::manage(new Gtk::Entry());
    e_x2->set_hexpand(true);
    grid->attach(*e_x2, 2, 2, 2, 1);

    Gtk::Label *l_y2 = Gtk::manage(new Gtk::Label("Y: "));
    grid->attach(*l_y2, 1, 3, 1, 1);

    Gtk::Entry *e_y2 = Gtk::manage(new Gtk::Entry());
    e_y2->set_hexpand(true);
    grid->attach(*e_y2, 2, 3, 2, 1);

    Gtk::Label *l_3 = Gtk::manage(new Gtk::Label("Enter Coordinates of Bottom-Right Corner  "));
    grid->attach(*l_3, 0, 4, 1, 1);

    Gtk::Label *l_x3 = Gtk::manage(new Gtk::Label("X: "));
    grid->attach(*l_x3, 1, 4, 1, 1);


    Gtk::Entry *e_x3 = Gtk::manage(new Gtk::Entry());
    e_x3->set_hexpand(true);
    grid->attach(*e_x3, 2, 4, 2, 1);

    Gtk::Label *l_y3 = Gtk::manage(new Gtk::Label("Y: "));
    grid->attach(*l_y3, 1, 5, 1, 1);

    Gtk::Entry *e_y3 = Gtk::manage(new Gtk::Entry());
    e_y3->set_hexpand(true);
    grid->attach(*e_y3, 2, 5, 2, 1);

    Gtk::Label *l_4 = Gtk::manage(new Gtk::Label("Enter Coordinates of Bottom-Left Corner  "));
    grid->attach(*l_4, 0, 6, 1, 1);

    Gtk::Label *l_x4 = Gtk::manage(new Gtk::Label("X: "));
    grid->attach(*l_x4, 1, 6, 1, 1);


    Gtk::Entry *e_x4 = Gtk::manage(new Gtk::Entry());
    e_x4->set_hexpand(true);
    grid->attach(*e_x4, 2, 6, 2, 1);

    Gtk::Label *l_y4 = Gtk::manage(new Gtk::Label("Y: "));
    grid->attach(*l_y4, 1, 7, 1, 1);

    Gtk::Entry *e_y4 = Gtk::manage(new Gtk::Entry());
    e_y4->set_hexpand(true);
    grid->attach(*e_y4, 2, 7, 2, 1);

    show_all_children();


    Gtk::Button *bwarp = Gtk::manage(new Gtk::Button("Warp"));
    bwarp->signal_clicked().connect(sigc::bind<Gtk::Entry*, Gtk::Entry*, Gtk::Entry*, Gtk::Entry* >(sigc::mem_fun(*this, &Warp_Coordinates::on_warp_click_1), e_x1,e_y1,e_x2,e_y2));
    bwarp->signal_clicked().connect(sigc::bind<Gtk::Entry*, Gtk::Entry*, Gtk::Entry*, Gtk::Entry* >(sigc::mem_fun(*this, &Warp_Coordinates::on_warp_click_2), e_x3,e_y3,e_x4,e_y4));

    grid->attach(*bwarp, 3, 8, 1, 1);

    vbox->show_all();
}


void Warp_Coordinates::on_warp_click_1(Gtk::Entry *e_x1,Gtk::Entry *e_y1,Gtk::Entry *e_x2,Gtk::Entry *e_y2){
    float x1=0,y1=0,x2=0,y2=0;
    char s_x1[15],s_y1[15],s_x2[15],s_y2[15];
    copy_string4(s_x1,e_x1->get_text());
    copy_string4(s_x2,e_x2->get_text());
    copy_string4(s_y1,e_y1->get_text());
    copy_string4(s_y2,e_y2->get_text());
    if(!is_number4(s_x1)||!is_number4(s_x2)||!is_number4(s_y1)||!is_number4(s_y2)){
        dialog("Please Enter Valid Numbers!");
    }
    else{
        sscanf(s_x1,"%f",&x1);
        sscanf(s_y1,"%f",&y1);
        sscanf(s_x2,"%f",&x2);
        sscanf(s_y2,"%f",&y2);

        if((x1<0||x1>100)||(y1<0||y1>100)||(x2<0||x2>100)||(y2<0||y2>100)){dialog("Please Enter Valid Numbers!");}
        else{
            x1/=100;x2/=100;y1/=100;y2/=100;
            y1=1-y1;
            swap_numbers4(x1,y1);
            y2=1-y2;
            swap_numbers4(x2,y2);

            FILE*warp_coordinates=fopen("Program_Files/Temp_Files/warp_Coordinates_1","wb+");
            if(warp_coordinates==NULL){dialog("Sorry! Unable to Warp Image.");}
            else{

                fwrite(&x1,sizeof(x1),1,warp_coordinates);
                fwrite(&y1,sizeof(y1),1,warp_coordinates);
                fwrite(&x2,sizeof(x2),1,warp_coordinates);
                fwrite(&y2,sizeof(y2),1,warp_coordinates);
                fclose(warp_coordinates);

            }
            }

    }
    return;


}

void Warp_Coordinates::on_warp_click_2(Gtk::Entry *e_x1,Gtk::Entry *e_y1,Gtk::Entry *e_x2,Gtk::Entry *e_y2){
    float x1=0,y1=0,x2=0,y2=0;
    char s_x1[15],s_y1[15],s_x2[15],s_y2[15];
    copy_string4(s_x1,e_x1->get_text());
    copy_string4(s_x2,e_x2->get_text());
    copy_string4(s_y1,e_y1->get_text());
    copy_string4(s_y2,e_y2->get_text());
    if(!is_number4(s_x1)||!is_number4(s_x2)||!is_number4(s_y1)||!is_number4(s_y2)){
        dialog("Please Enter Valid Numbers!");
    }
    else{
        char s[100];
        sprintf(s,"%s %s %s %s",s_x1,s_y1,s_x2,s_y2);

//        sscanf(s,"%d %d %d %d",&x1,&y1,&x2,&y2);
        sscanf(s_x1,"%f",&x1);
        sscanf(s_y1,"%f",&y1);
        sscanf(s_x2,"%f",&x2);
        sscanf(s_y2,"%f",&y2);
//        printf("Numbers: %f,%f,%f,%f!",x1,y1,x2,y2);

        if((x1<0||x1>100)||(y1<0||y1>100)||(x2<0||x2>100)||(y2<0||y2>100)){dialog("Please Enter Valid Numbers!");}
        else{
            x1/=100;x2/=100;y1/=100;y2/=100;
            y1=1-y1;
            swap_numbers4(x1,y1);
            y2=1-y2;
            swap_numbers4(x2,y2);

            FILE*warp_coordinates=fopen("Program_Files/Temp_Files/warp_Coordinates_2","wb+");
            if(warp_coordinates==NULL){dialog("Sorry! Unable to warp Image.");}
            else{

                fwrite(&x1,sizeof(x1),1,warp_coordinates);
                fwrite(&y1,sizeof(y1),1,warp_coordinates);
                fwrite(&x2,sizeof(x2),1,warp_coordinates);
                fwrite(&y2,sizeof(y2),1,warp_coordinates);
                fclose(warp_coordinates);

            }

            hide();
            }

    }

}


Warp_Coordinates::~Warp_Coordinates()
{
    //dtor
}

void Warp_Coordinates::dialog(Glib::ustring msg)
{
    Gtk::MessageDialog dlg(msg, false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
    dlg.set_title("Digital Image Processor");
    dlg.run();
}
