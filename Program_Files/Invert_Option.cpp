#include "Invert_Option.h"

Invert_Option::Invert_Option()
{
    //ctor
    int x1=-1;
    FILE*inv_opt=fopen("Program_Files/Temp_Files/Invert_Option","wb+");
    if(inv_opt!=NULL){
        fwrite(&x1,sizeof(x1),1,inv_opt);
        fclose(inv_opt);
    }
    set_modal(true);







    Gtk::Box *vbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0));
    add(*vbox);

    set_default_size(240, 50);
    set_title("Choose Invert Option");
    set_position(Gtk::WIN_POS_CENTER);

    Gtk::Grid *grid = Gtk::manage(new Gtk::Grid);
    grid->set_border_width(10);
    grid->set_row_spacing(30);
    vbox->add(*grid);


    Gtk::Button *bh = Gtk::manage(new Gtk::Button("Invert Horizontally"));
    bh->set_hexpand(true);
    bh->signal_clicked().connect(sigc::mem_fun(*this, &Invert_Option::on_invert_h_click));
    grid->attach(*bh, 0, 0, 1, 2);

    Gtk::Button *bv = Gtk::manage(new Gtk::Button("Invert Vertically"));
    bv->set_hexpand(true);
    bv->signal_clicked().connect(sigc::mem_fun(*this, &Invert_Option::on_invert_v_click));
    grid->attach(*bv, 0, 1, 1, 2);


    vbox->show_all();
}

Invert_Option::~Invert_Option()
{
    //dtor
}

void Invert_Option::on_invert_h_click(){

    int x1=0;
    FILE*inv_opt=fopen("Program_Files/Temp_Files/Invert_Option","wb+");
    if(inv_opt==NULL){dialog("Sorry! Unable to Invert Image.");}
    else{
        fwrite(&x1,sizeof(x1),1,inv_opt);
        fclose(inv_opt);
        hide();
    }
    return;

};

void Invert_Option::on_invert_v_click(){

    int x1=1;
    FILE*inv_opt=fopen("Program_Files/Temp_Files/Invert_Option","wb+");
    if(inv_opt==NULL){dialog("Sorry! Unable to Invert Image.");}
    else{
        fwrite(&x1,sizeof(x1),1,inv_opt);
        fclose(inv_opt);
        hide();
    }
    return;

};

void Invert_Option::dialog(Glib::ustring msg)
{
    Gtk::MessageDialog dlg(msg, false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
    dlg.set_title("Digital Image Processor");
    dlg.run();
}
