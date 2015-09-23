#include<gtkmm.h>
#include "home_window.h"

#include "functions.h"

#include<iostream>
#include<cstring>

#include"Enter_Crop_Coordinates.h"
#include"Enter_Angle.h"
#include"Invert_Option.h"
#include"Stretch_Option.h"
#include"Enter_Blur_Radius.h"
#include"Warp_Coordinates.h"

#define OPACITY_IN 0
#define OPACITY_IN_1 0.2
#define OPACITY_OUT 1
#define PREVIEW_HEIGHT 500.0
#define PREVIEW_WIDTH 800.0

home::home()
{
    curr_image=NULL;
    height=0;
    width=0;
    original_filename[0]='\0';
    current_filename[0]='\0';
    in_file=NULL;
    bin_count=0;
    output_count=0;
//    sprintf(location_input,"/home/shubham/Desktop/Digital IMG processing stage 2/Tutorial3/Input");
    sprintf(location_output,"Output_Files");
    sprintf(location_bin,"Program_Files/Temp_Files");


    is_window_open=false;


    set_default_size(1500, 500);
    set_title("On-Screen Dialog Box");
    set_position(Gtk::WIN_POS_CENTER);
//    set_resizable(false);


    Gtk::HPaned* pane=Gtk::manage(new Gtk::HPaned);
    add(*pane);



	Gtk::Box* box2 = Gtk::manage(new Gtk::Box());
	box2->set_orientation (Gtk::ORIENTATION_VERTICAL);
	box2->set_spacing(10);
	box2->set_border_width(30);
    pane->add2(*box2);

    image = Gtk::manage(new Gtk::Image());
    image->set("Program_Files/welcome.jpg");

    l_preview_name = Gtk::manage(new Gtk::Label);

	box2->pack_start (*image,true,0);




    Gtk::Box *vbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0));
    pane->add1(*vbox);
    vbox->set_border_width(10);



    Gtk::Grid *grid = Gtk::manage(new Gtk::Grid);
    grid->set_border_width(30);
    grid->set_column_spacing(10);
    grid->set_row_spacing(5);
    vbox->add(*grid);


 //   Gtk::Label *l_intro = Gtk::manage(new Gtk::Label("DIGITAL IMAGE PROCESSING"));
 //   grid->attach(*l_intro, 0,3 , 1, 3);

    Gtk::Button *open_button = Gtk::manage(new Gtk::Button("Open"));
    open_button->set_hexpand(true);
    open_button->signal_clicked().connect(sigc::mem_fun(*this, &home::on_open_click));
    grid->attach(*open_button, 1, 1, 2, 1);

    Gtk::Button *exit_button = Gtk::manage(new Gtk::Button("Exit"));
    exit_button->set_hexpand(true);
    exit_button->signal_clicked().connect(sigc::mem_fun(*this, &home::on_exit_click));
    grid->attach(*exit_button, 4, 1, 2, 1);

    Gtk::Button *save_button= Gtk::manage(new Gtk::Button("Save"));
    save_button->signal_clicked().connect(sigc::mem_fun(*this, &home::on_save_click));
    save_button->set_hexpand(true);
    grid->attach(*save_button, 1, 2, 2, 1);

    Gtk::Button *undo_button = Gtk::manage(new Gtk::Button("Undo"));
    undo_button->set_hexpand(true);
    undo_button->signal_clicked().connect(sigc::mem_fun(*this, &home::on_undo_click));
    grid->attach(*undo_button, 4, 2, 2, 1);

    Gtk::Label *l_functions = Gtk::manage(new Gtk::Label);
    l_functions->set_markup("<b><span color='blue'>FUNCTIONS</span></b>");
    l_functions->set_hexpand(true);
    grid->attach(*l_functions, 1,4 ,5 , 1);

    Gtk::Label *l_blank = Gtk::manage(new Gtk::Label(" "));
    grid->attach(*l_blank, 1,3 , 5, 1);

    Gtk::Button *crop_button = Gtk::manage(new Gtk::Button("Crop"));
    crop_button->set_hexpand(true);
    crop_button->signal_clicked().connect(sigc::mem_fun(*this, &home::on_crop_click));
    grid->attach(*crop_button,1,5, 2, 1);

    Gtk::Button *rotate_button = Gtk::manage(new Gtk::Button("Rotate"));
    rotate_button->set_hexpand(true);
    rotate_button->signal_clicked().connect(sigc::mem_fun(*this, &home::on_rotate_click));
    grid->attach(*rotate_button, 1,8, 2, 1);

    Gtk::Button *invert_button = Gtk::manage(new Gtk::Button("Invert"));
    invert_button->set_hexpand(true);
    invert_button->signal_clicked().connect(sigc::mem_fun(*this, &home::on_invert_click));
    grid->attach(*invert_button, 1,9 ,2, 1);

    Gtk::Button *grayscale_button = Gtk::manage(new Gtk::Button("Grayscale"));
    grayscale_button->set_hexpand(true);
    grayscale_button->signal_clicked().connect(sigc::mem_fun(*this, &home::on_grayscale_click));
    grid->attach(*grayscale_button, 4,5, 2, 1);

    Gtk::Button *halftone_button = Gtk::manage(new Gtk::Button("Halftone"));
    halftone_button->set_hexpand(true);
    halftone_button->signal_clicked().connect(sigc::mem_fun(*this, &home::on_halftone_click));
    grid->attach(*halftone_button, 4,12, 2, 1);

    Gtk::Button *detect_edges_button = Gtk::manage(new Gtk::Button("Detect Edges"));
    detect_edges_button->set_hexpand(true);
    detect_edges_button->signal_clicked().connect(sigc::mem_fun(*this, &home::on_edge_click));
    grid->attach(*detect_edges_button, 4,11, 2, 1);

    Gtk::Button *stretch_button = Gtk::manage(new Gtk::Button("Stretch"));
    stretch_button->set_hexpand(true);
    stretch_button->signal_clicked().connect(sigc::mem_fun(*this, &home::on_stretch_click));
    grid->attach(*stretch_button, 1,6, 2, 1);

    Gtk::Button *blur_button = Gtk::manage(new Gtk::Button("Blur"));
    blur_button->set_hexpand(true);
    blur_button->signal_clicked().connect(sigc::mem_fun(*this, &home::on_blur_click));
    grid->attach(*blur_button, 1,10, 2, 1);

    Gtk::Button *warp_button = Gtk::manage(new Gtk::Button("Warp"));
    warp_button->set_hexpand(true);
    warp_button->signal_clicked().connect(sigc::mem_fun(*this, &home::on_warp_click));
    grid->attach(*warp_button, 1,7, 2, 1);

    Gtk::Button *contrast_button = Gtk::manage(new Gtk::Button("Contrast"));
    contrast_button->set_hexpand(true);
    contrast_button->signal_clicked().connect(sigc::mem_fun(*this, &home::on_contrast_click));
    grid->attach(*contrast_button, 1,12, 2, 1);

    Gtk::Button *f1_button = Gtk::manage(new Gtk::Button("Dither"));
    f1_button->set_hexpand(true);
    f1_button->signal_clicked().connect(sigc::mem_fun(*this, &home::on_f1_click));
    grid->attach(*f1_button, 4,13, 2, 1);

    Gtk::Button *f2_button = Gtk::manage(new Gtk::Button("Sepia"));
    f2_button->set_hexpand(true);
    f2_button->signal_clicked().connect(sigc::mem_fun(*this, &home::on_f2_click));
    grid->attach(*f2_button, 4,7, 2, 1);

    Gtk::Button *f3_button = Gtk::manage(new Gtk::Button("iMagik"));
    f3_button->set_hexpand(true);
    f3_button->signal_clicked().connect(sigc::mem_fun(*this, &home::on_f3_click));
    grid->attach(*f3_button, 1,13, 2, 1);

    Gtk::Button *f4_button = Gtk::manage(new Gtk::Button("Negative"));
    f4_button->set_hexpand(true);
    f4_button->signal_clicked().connect(sigc::mem_fun(*this, &home::on_f4_click));
    grid->attach(*f4_button, 4,6, 2, 1);

    Gtk::Button *f5_button = Gtk::manage(new Gtk::Button("Hue"));
    f5_button->set_hexpand(true);
    f5_button->signal_clicked().connect(sigc::mem_fun(*this, &home::on_f5_click));
    grid->attach(*f5_button, 4,8, 2, 1);

    Gtk::Button *f6_button = Gtk::manage(new Gtk::Button("Salt & Pepper"));
    f6_button->set_hexpand(true);
    f6_button->signal_clicked().connect(sigc::mem_fun(*this, &home::on_f6_click));
    grid->attach(*f6_button, 4,9, 2, 1);

//    Gtk::Button *f7_button = Gtk::manage(new Gtk::Button("Colorness"));
//    f7_button->set_hexpand(true);
//    f7_button->signal_clicked().connect(sigc::mem_fun(*this, &home::on_f7_click));
//    grid->attach(*f7_button, 4,14, 2, 1);

    Gtk::Button *f8_button = Gtk::manage(new Gtk::Button("Quick Blur"));
    f8_button->set_hexpand(true);
    f8_button->signal_clicked().connect(sigc::mem_fun(*this, &home::on_f8_click));
    grid->attach(*f8_button, 1,11, 2, 1);

    Gtk::Button *f9_button = Gtk::manage(new Gtk::Button("Add Watermark"));
    f9_button->set_hexpand(true);
    f9_button->signal_clicked().connect(sigc::mem_fun(*this, &home::on_f9_click));
    grid->attach(*f9_button, 4,10, 2, 1);

    vbox->show_all();
    show_all_children();
}

home::~home()
{
    //dtor

    if(in_file!=NULL){fclose(in_file);}




    std::map<int, crop_popup*>::iterator iter2;
    for (iter2 = popups2.begin(); iter2 != popups2.end(); iter2++)
    {
        crop_popup *crop_popup_window= iter2->second;



        delete crop_popup_window->crop_popup_window;
        delete crop_popup_window;
    }

    std::map<int, rotate_popup*>::iterator iter3;
    for (iter3 = popups3.begin(); iter3 != popups3.end(); iter3++)
    {
        rotate_popup *rotate_popup_window= iter3->second;



        delete rotate_popup_window->rotate_popup_window;
        delete rotate_popup_window;
    }

    std::map<int, invert_popup*>::iterator iter4;
    for (iter4 = popups4.begin(); iter4 != popups4.end(); iter4++)
    {
        invert_popup *invert_popup_window= iter4->second;



        delete invert_popup_window->invert_popup_window;
        delete invert_popup_window;
    }

    std::map<int, stretch_popup*>::iterator iter5;
    for (iter5 = popups5.begin(); iter5 != popups5.end(); iter5++)
    {
        stretch_popup *stretch_popup_window= iter5->second;



        delete stretch_popup_window->stretch_popup_window;
        delete stretch_popup_window;
    }

    std::map<int, blur_popup*>::iterator iter6;
    for (iter6 = popups6.begin(); iter6 != popups6.end(); iter6++)
    {
        blur_popup *blur_popup_window= iter6->second;



        delete blur_popup_window->blur_popup_window;
        delete blur_popup_window;
    }

    std::map<int, warp_popup*>::iterator iter7;
    for (iter7 = popups7.begin(); iter7 != popups7.end(); iter7++)
    {
        warp_popup *warp_popup_window= iter7->second;



        delete warp_popup_window->warp_popup_window;
        delete warp_popup_window;
    }

    std::map<int, hue_popup*>::iterator iter8;
    for (iter8 = popups8.begin(); iter8 != popups8.end(); iter8++)
    {
        hue_popup *hue_popup_window= iter8->second;



        delete hue_popup_window->hue_popup_window;
        delete hue_popup_window;
    }

    std::map<int, qblur_popup*>::iterator iter9;
    for (iter9 = popups9.begin(); iter9 != popups9.end(); iter9++)
    {
        qblur_popup *qblur_popup_window= iter9->second;



        delete qblur_popup_window->qblur_popup_window;
        delete qblur_popup_window;
    }

}

void home::set_image_preview(){

    char preview_fname[100];
    sprintf(preview_fname,"%s/preview-%d.bmp",location_bin,bin_count);
    int prev_height,prev_width;
    double scale_factor;
    if(height>PREVIEW_HEIGHT){
        if(width>PREVIEW_WIDTH)
            {scale_factor=minimum(PREVIEW_HEIGHT*1.0/height,PREVIEW_WIDTH*1.0/width);}
        else {scale_factor=PREVIEW_HEIGHT*1.0/height;}
    }
    else if(width>PREVIEW_WIDTH)
            {scale_factor=PREVIEW_WIDTH*1.0/width;}
        else {scale_factor=1;}
    int p_height,p_width;
    p_height=height*scale_factor;
    p_width=width*scale_factor;

    pixel**img_preview=stretch_image(curr_image,height,width,scale_factor,scale_factor);
    if(img_preview==NULL){dialog("Sorry! Unable to Generate Preview.");}
    else{
        FILE*out_file=save_img_to_file(img_preview,p_height,p_width,in_file,preview_fname);
        delete_image(img_preview,p_height,p_width);
        if(out_file==NULL){dialog("Sorry! Unable to Generate Preview.");}
        else {image->clear();image->set(preview_fname);fclose(out_file);}
    }
    return;

};



void home::on_crop_popup_close(crop_popup *crop_popup_window)
{
    is_window_open=false;
    set_opacity(OPACITY_OUT);
    float x1,y1,x2,y2;
    char loc_file[100];
    sprintf(loc_file,"%s/Crop_Coordinates",location_bin);
    FILE*crop_coordinates=fopen(loc_file,"rb+");
        if(crop_coordinates==NULL){dialog("Sorry! Unable to Crop Image.");return;}
        else{
            fread(&x1,sizeof(x1),1,crop_coordinates);
            fread(&y1,sizeof(y1),1,crop_coordinates);
            fread(&x2,sizeof(x2),1,crop_coordinates);
            fread(&y2,sizeof(y2),1,crop_coordinates);
            fclose(crop_coordinates);
        }

    if(x1==-1||y1==-1||x2==-1||y2==-1){return;}
    int ix1,iy1,ix2,iy2;
    ix1=x1*height;iy1=y1*width;ix2=x2*height;iy2=y2*width;
    curr_image=crop_image(curr_image,height,width,ix1,iy1,ix2,iy2);
    height=ix2-ix1;
    width=iy2-iy1;

/***FILE_HANDLING_COMMON***/

    char outfilename[100];
    sprintf(outfilename,"%s/temp-%d.bmp",location_bin,bin_count);
    FILE*out_file=save_img_to_file(curr_image,height,width,in_file,outfilename);
    if(out_file==NULL){dialog("Sorry! Unable to Crop Image.");return;}
    fclose(in_file);fclose(out_file);
    in_file=fopen(outfilename,"rb+");
    if(in_file==NULL){dialog("Sorry! Unable to Crop Image.");hide();return;}

    /***PREVIEW_HANDLING_COMMON***/

    set_image_preview();

    bin_count++;


    delete crop_popup_window->crop_popup_window;
    delete crop_popup_window;
    return;
}

void home::on_rotate_popup_close(rotate_popup *rotate_popup_window)
{
    is_window_open=false;
    set_opacity(OPACITY_OUT);
    float x1;
    char loc_file[100];
    sprintf(loc_file,"%s/Rotate_Angle",location_bin);
    FILE*rotate_angle=fopen(loc_file,"rb+");
    if(rotate_angle==NULL){dialog("Sorry! Unable to Rotate Image.");return;}
    else{
        fread(&x1,sizeof(x1),1,rotate_angle);
        fclose(rotate_angle);
    }
    if(x1==-1){return;}
    int rot_angle=x1;
    int origin_x=height/2,origin_y=width/2;

    double pi=3.14159265359;
    double theta=(rot_angle*pi)/180;
    theta=-theta;
    double sine_theta=sin(theta),cos_theta=cos(theta);

    int new_height=maximum(fabs(height*cos_theta+width*sine_theta),fabs(height*cos_theta-width*sine_theta));
    int new_width=maximum(fabs(width*cos_theta+height*sine_theta),fabs(width*cos_theta-height*sine_theta));

    curr_image=rotate_image(curr_image,height,width,origin_x,origin_y,rot_angle);
    height=new_height;
    width=new_width;

/***FILE_HANDLING_COMMON***/

    char outfilename[100];
    sprintf(outfilename,"%s/temp-%d.bmp",location_bin,bin_count);

    FILE*out_file=save_img_to_file(curr_image,height,width,in_file,outfilename);
    if(out_file==NULL){dialog("Sorry! Unable to Rotate Image.");return;}
    fclose(in_file);fclose(out_file);
    in_file=fopen(outfilename,"rb+");
    if(in_file==NULL){dialog("Sorry! Unable to Rotate Image.");hide();return;}

    /***PREVIEW_HANDLING_COMMON***/

    set_image_preview();

    bin_count++;

    delete rotate_popup_window->rotate_popup_window;
    delete rotate_popup_window;
    return;
}


void home::on_invert_popup_close(invert_popup *invert_popup_window){

    is_window_open=false;
    set_opacity(OPACITY_OUT);
    int x1;
    char loc_file[100];
    sprintf(loc_file,"%s/Invert_Option",location_bin);
    FILE*inv_opt=fopen(loc_file,"rb+");
    if(inv_opt==NULL){dialog("Sorry! Unable to Invert Image.");return;}
    else{
        fread(&x1,sizeof(x1),1,inv_opt);
        fclose(inv_opt);
    }
    if(x1==-1){return;}
    switch(x1){
        case 0: curr_image=invert_horizontally(curr_image,height,width);break;
        case 1: curr_image=invert_vertically(curr_image,height,width);break;
        default: dialog("Sorry! Unable to Invert Image.");
    }

/***FILE_HANDLING_COMMON***/

    char outfilename[100];
    sprintf(outfilename,"%s/temp-%d.bmp",location_bin,bin_count);

    FILE*out_file=save_img_to_file(curr_image,height,width,in_file,outfilename);
    if(out_file==NULL){dialog("Sorry! Unable to Invert Image.");return;}
    fclose(in_file);fclose(out_file);
    in_file=fopen(outfilename,"rb+");
    if(in_file==NULL){dialog("Sorry! Unable to Invert Image.");hide();return;}

    /***PREVIEW_HANDLING_COMMON***/

    set_image_preview();

    bin_count++;

    delete invert_popup_window->invert_popup_window;
    delete invert_popup_window;
    return;

};

void home::on_stretch_popup_close(stretch_popup *stretch_popup_window){

    is_window_open=false;
    set_opacity(OPACITY_OUT);
    float x1,y1;
    char loc_file[100];
    sprintf(loc_file,"%s/stretch_coordinates",location_bin);
    FILE*stretch_coordinates=fopen(loc_file,"rb+");
    if(stretch_coordinates==NULL){dialog("Sorry! Unable to Stretch Image.");return;}
    else{
        fread(&x1,sizeof(x1),1,stretch_coordinates);
        fread(&y1,sizeof(y1),1,stretch_coordinates);
        fclose(stretch_coordinates);
    }
    if(x1==-1||y1==-1){return;}
    double ver_coeff,hor_coeff;
    ver_coeff=x1;hor_coeff=y1;

    pixel**temp_image=stretch_image(curr_image,height,width,ver_coeff,hor_coeff);
    delete_image(curr_image,height,width);
    curr_image=temp_image;

    height*=ver_coeff;
    width*=hor_coeff;

    /***FILE_HANDLING_COMMON***/

    char outfilename[100];
    sprintf(outfilename,"%s/temp-%d.bmp",location_bin,bin_count);

    FILE*out_file=save_img_to_file(curr_image,height,width,in_file,outfilename);
    if(out_file==NULL){dialog("Sorry! Unable to Stretch Image.");return;}
    fclose(in_file);fclose(out_file);
    in_file=fopen(outfilename,"rb+");
    if(in_file==NULL){dialog("Sorry! Unable to Stretch Image.");hide();return;}

    /***PREVIEW_HANDLING_COMMON***/

    set_image_preview();

    bin_count++;




    delete stretch_popup_window->stretch_popup_window;
    delete stretch_popup_window;
    return;
};


void home::on_blur_popup_close(blur_popup *blur_popup_window){

    set_opacity(OPACITY_OUT);
    is_window_open=false;
    float x1;
    char loc_file[100];
    sprintf(loc_file,"%s/blur_coordinates",location_bin);
    FILE*blur_coordinates=fopen(loc_file,"rb+");

    if(blur_coordinates==NULL){dialog("Sorry! Unable to Blur Image.");return;}
    else{
        fread(&x1,sizeof(x1),1,blur_coordinates);
        fclose(blur_coordinates);
    }
    if(x1==-1){return;}

    int blur_radius=(int)x1;

//    curr_image=blur(curr_image,height,width,blur_radius);
    curr_image=box_blur(curr_image,height,width,blur_radius);



    /***FILE_HANDLING_COMMON***/

    char outfilename[100];
    sprintf(outfilename,"%s/temp-%d.bmp",location_bin,bin_count);

    FILE*out_file=save_img_to_file(curr_image,height,width,in_file,outfilename);
    if(out_file==NULL){dialog("Sorry! Unable to Blur Image.");return;}
    fclose(in_file);fclose(out_file);
    in_file=fopen(outfilename,"rb+");
    if(in_file==NULL){dialog("Sorry! Unable to Blur Image.");hide();return;}

    /***PREVIEW_HANDLING_COMMON***/

    set_image_preview();

    bin_count++;

    delete blur_popup_window->blur_popup_window;
    delete blur_popup_window;
    return;
};

void home::on_warp_popup_close(warp_popup *warp_popup_window){

    is_window_open=false;
    set_opacity(OPACITY_OUT);

    char loc_file[100];
    sprintf(loc_file,"%s/warp_Coordinates_1",location_bin);

    FILE*warp_coordinates_1=fopen(loc_file,"rb+");

    sprintf(loc_file,"%s/warp_Coordinates_2",location_bin);

    FILE*warp_coordinates_2=fopen(loc_file,"rb+");
    float x1,y1,x2,y2,x3,x4,y3,y4;
    if(warp_coordinates_1==NULL||warp_coordinates_2==NULL){dialog("Sorry! Unable to Warp Image.");return;}
    else{
        fread(&x1,sizeof(x1),1,warp_coordinates_1);
        fread(&y1,sizeof(y1),1,warp_coordinates_1);
        fread(&x2,sizeof(x2),1,warp_coordinates_1);
        fread(&y2,sizeof(y2),1,warp_coordinates_1);
        fread(&x3,sizeof(x3),1,warp_coordinates_2);
        fread(&y3,sizeof(y3),1,warp_coordinates_2);
        fread(&x4,sizeof(x4),1,warp_coordinates_2);
        fread(&y4,sizeof(y4),1,warp_coordinates_2);
        fclose(warp_coordinates_1);
        fclose(warp_coordinates_2);
    }
    if(x1==-1||x2==-1||x3==-1||x4==-1||y1==-1||y2==-1||y3==-1||y4==-1){return;}
    curr_image=warp_image(curr_image,height,width,x1,y1,x2,y2,x3,y3,x4,y4);



    /***FILE_HANDLING_COMMON***/

    char outfilename[100];
    sprintf(outfilename,"%s/temp-%d.bmp",location_bin,bin_count);

    FILE*out_file=save_img_to_file(curr_image,height,width,in_file,outfilename);
    if(out_file==NULL){dialog("Sorry! Unable to Warp Image.");return;}
    fclose(in_file);fclose(out_file);
    in_file=fopen(outfilename,"rb+");
    if(in_file==NULL){dialog("Sorry! Unable to Warp Image.");hide();return;}

    /***PREVIEW_HANDLING_COMMON***/

    set_image_preview();

    bin_count++;

    delete warp_popup_window->warp_popup_window;
    delete warp_popup_window;
    return;
};

void home::on_hue_popup_close(hue_popup *hue_popup_window)
{
    is_window_open=false;
    set_opacity(OPACITY_OUT);
    float x1;
    char loc_file[100];
    sprintf(loc_file,"%s/Rotate_Hue",location_bin);
    FILE*rotate_Hue=fopen(loc_file,"rb+");
    if(rotate_Hue==NULL){dialog("Sorry! Unable to Rotate Image.");return;}
    else{
        fread(&x1,sizeof(x1),1,rotate_Hue);
        fclose(rotate_Hue);
    }
    if(x1==-1){return;}
    int rot_Hue=x1*100;


    curr_image=add_hue_blue(curr_image,height,width,rot_Hue);

/***FILE_HANDLING_COMMON***/

    char outfilename[100];
    sprintf(outfilename,"%s/temp-%d.bmp",location_bin,bin_count);

    FILE*out_file=save_img_to_file(curr_image,height,width,in_file,outfilename);
    if(out_file==NULL){dialog("Sorry! Unable to change Hue.");return;}
    fclose(in_file);fclose(out_file);
    in_file=fopen(outfilename,"rb+");
    if(in_file==NULL){dialog("Sorry! Unable to change Hue.");hide();return;}

    /***PREVIEW_HANDLING_COMMON***/

    set_image_preview();

    bin_count++;

    delete hue_popup_window->hue_popup_window;
    delete hue_popup_window;
    return;
}

void home::on_qblur_popup_close(qblur_popup *qblur_popup_window){

    set_opacity(OPACITY_OUT);
    is_window_open=false;
    float x1;
    char loc_file[100];
    sprintf(loc_file,"%s/qblur_coordinates",location_bin);
    FILE*qblur_coordinates=fopen(loc_file,"rb+");

    if(qblur_coordinates==NULL){dialog("Sorry! Unable to Quick Blur Image.");return;}
    else{
        fread(&x1,sizeof(x1),1,qblur_coordinates);
        fclose(qblur_coordinates);
    }
    if(x1==-1){return;}

    int qblur_radius=(int)x1;

    curr_image=box_blur(curr_image,height,width,qblur_radius);



    /***FILE_HANDLING_COMMON***/

    char outfilename[100];
    sprintf(outfilename,"%s/temp-%d.bmp",location_bin,bin_count);

    FILE*out_file=save_img_to_file(curr_image,height,width,in_file,outfilename);
    if(out_file==NULL){dialog("Sorry! Unable to qblur Image.");return;}
    fclose(in_file);fclose(out_file);
    in_file=fopen(outfilename,"rb+");
    if(in_file==NULL){dialog("Sorry! Unable to qblur Image.");hide();return;}

    /***PREVIEW_HANDLING_COMMON***/

    set_image_preview();

    bin_count++;

    delete qblur_popup_window->qblur_popup_window;
    delete qblur_popup_window;
    return;
};


/**FUNCTIONS**///START

void copy_string0(char s1[],string s2){
    int i=0;
    for(;s2[i]!='\0';)
    {
        if(i==200){s1[0]='\0';return;}
        s1[i]=s2[i];
        i++;
    }
    s1[i]='\0';
    return;
}

bool change_filename(char inputfile[]){
    int k=0,i=0;
    char*new_name=new char [200];
    if(new_name==NULL){return false;}
    for(i=0;inputfile[i]!='\0';){
        new_name[k]=inputfile[i];
        k++;i++;
        if(inputfile[i-1]=='/'){k=0;}
    }
    if(i==0){return false;}
    k--;
    if(k<=3){return false;}
    if(!(new_name[k-3]=='.'&&new_name[k-2]=='b'&&new_name[k-1]=='m'&&new_name[k]=='p')){return false;}
    new_name[k-3]='\0';
    strcpy(inputfile,new_name);
    delete[] new_name;
    return true;

}
/**FUNCTIONS**///END

void home::on_open_click(){

    char inputfile[200]={"\0"};

    if(is_window_open){dialog("You cannot open multiple windows.");return;}
    else{is_window_open=true;}

    set_opacity(OPACITY_IN);

    Gtk::FileChooserDialog fcdialog("Open image",
	                              Gtk::FILE_CHOOSER_ACTION_OPEN);
	fcdialog.add_button (Gtk::Stock::OPEN,
	                   Gtk::RESPONSE_ACCEPT);
	fcdialog.add_button (Gtk::Stock::CANCEL,
	                   Gtk::RESPONSE_CANCEL);

	Glib::RefPtr<Gtk::FileFilter> filter =
		Gtk::FileFilter::create();
	filter->add_pixbuf_formats();
	filter->set_name("Images");
	fcdialog.add_filter (filter);

	const int response = fcdialog.run();
	fcdialog.hide();

	is_window_open=false;

	switch (response)
	{
		case Gtk::RESPONSE_ACCEPT:
			copy_string0(inputfile,fcdialog.get_filename());
			break;
		default:
			break;
	}




    set_opacity(OPACITY_OUT);



    strcpy(original_filename,inputfile);

    if(!change_filename(original_filename)){dialog("Could Not Open Image.");return;}
    if(curr_image!=NULL){delete_image(curr_image,height,width);}

    if(in_file!=NULL){fclose(in_file);}

    curr_image=image_pixel_array(inputfile);
    if(curr_image==NULL){dialog("Could Not Open Image.");return;}
    height=image_height(inputfile);
    width=image_width(inputfile);
    if(height==0||width==0){delete[]curr_image;return;}
    in_file=fopen(inputfile,"rb+");

    /***FILE_HANDLING_COMMON***/

    char outfilename[100];
    sprintf(outfilename,"%s/temp-%d.bmp",location_bin,bin_count);

    FILE*out_file=save_img_to_file(curr_image,height,width,in_file,outfilename);
    if(out_file==NULL){dialog("Sorry! Unable to Open Image.");return;}
    fclose(in_file);fclose(out_file);
    in_file=fopen(outfilename,"rb+");
    if(in_file==NULL){dialog("Sorry! Unable to Open Image.");hide();return;}

    /***PREVIEW_HANDLING_COMMON***/

    set_image_preview();

    bin_count++;



    return;
};


void home::on_exit_click(){

    hide();
    return;
};


void home::on_save_click(){

    if(is_window_open){dialog("Please close previously opened windows first.");return;}

    if(curr_image==NULL){dialog("Please Open an Image First."); on_open_click();return;}
    char out_fname[100];
    sprintf(out_fname,"%s/%s-Output %d.bmp",location_output,original_filename,output_count);

    FILE*saved_image=save_img_to_file(curr_image,height,width,in_file,out_fname);
    char dialog_statement[150];
    sprintf(dialog_statement,"Image Saved Successfully as %s.",out_fname);
    if(saved_image==NULL){dialog("Unable to Save Image!");}
    else {dialog(dialog_statement);}
    output_count++;
};


void home::on_undo_click(){

    if(is_window_open){dialog("Please close previously opened windows first.");return;}
    char fname[100];
    if(bin_count==1){
        bin_count--;
        delete_image(curr_image,height,width);
        curr_image=NULL;
        fclose(in_file);
        in_file=NULL;
        image->clear();
        image->set("Program_Files/welcome.jpg");

    }
    else{

        if(bin_count==0){
            dialog("Please Open an Image first.");return;
        }
        else{
            bin_count-=2;
            sprintf(fname,"%s/temp-%d.bmp",location_bin,bin_count);
            delete_image(curr_image,height,width);
            curr_image==NULL;
            fclose(in_file);
            curr_image=image_pixel_array(fname);
            if(curr_image==NULL){dialog("Unable to Undo");dialog("Closing Application");hide();return;}
            height=image_height(fname);
            width=image_width(fname);
            if(height==0||width==0){dialog("Unable to Undo");dialog("Closing Application");hide();return;}
            in_file=fopen(fname,"rb+");
            set_image_preview();
            bin_count++;
        }

    /***PREVIEW_HANDLING_COMMON***/
    }


    return;

};


void home::on_crop_click(){


    if(curr_image==NULL){dialog("Please Open an Image First."); on_open_click();return;}

    if(is_window_open){dialog("Please close previously opened windows first.");return;}
    else{is_window_open=true;}

    set_opacity(OPACITY_IN);
    crop_popup *crop_popup_window = new crop_popup;
    crop_popup_window->crop_popup_window = new Enter_Crop_Coordinates;
    //popup->windowid = windowcnt;

    /*std::stringstream ss;
    ss << "Tutorial 6 - New Popup '" << windowcnt << "'";
    popup->popup->set_title(ss.str());*/

    crop_popup_window->crop_popup_window->signal_hide().connect(sigc::bind<crop_popup*>(sigc::mem_fun(*this, &home::on_crop_popup_close), crop_popup_window));

    //popups[windowcnt] = popup;
    //11111111windowcnt++;

    crop_popup_window->crop_popup_window->show();
};


void home::on_rotate_click(){


    if(curr_image==NULL){dialog("Please Open an Image First."); on_open_click();return;}

    if(is_window_open){dialog("Please close previously opened windows first.");return;}
    else{is_window_open=true;}

    set_opacity(OPACITY_IN);

    rotate_popup *rotate_popup_window = new rotate_popup;
    rotate_popup_window->rotate_popup_window = new Enter_Angle;
    //popup->windowid = windowcnt;

    /*std::stringstream ss;
    ss << "Tutorial 6 - New Popup '" << windowcnt << "'";
    popup->popup->set_title(ss.str());*/
    rotate_popup_window->rotate_popup_window->signal_hide().connect(sigc::bind<rotate_popup*>(sigc::mem_fun(*this, &home::on_rotate_popup_close), rotate_popup_window));

    //popups[windowcnt] = popup;
    //11111111windowcnt++;
    rotate_popup_window->rotate_popup_window->show();

};


void home::on_invert_click(){
    if(curr_image==NULL){dialog("Please Open an Image First."); on_open_click();return;}

    if(is_window_open){dialog("Please close previously opened windows first.");return;}
    else{is_window_open=true;}

    set_opacity(OPACITY_IN);

    invert_popup *invert_popup_window = new invert_popup;
    invert_popup_window->invert_popup_window = new Invert_Option;

  //  gtk_window_set_position(GTK_WINDOW(*(invert_popup_window->invert_popup_window)), GTK_WIN_POS_CENTER);

    //popup->windowid = windowcnt;

    /*std::stringstream ss;
    ss << "Tutorial 6 - New Popup '" << windowcnt << "'";
    popup->popup->set_title(ss.str());*/
    invert_popup_window->invert_popup_window->signal_hide().connect(sigc::bind<invert_popup*>(sigc::mem_fun(*this, &home::on_invert_popup_close), invert_popup_window));

    //popups[windowcnt] = popup;
    //11111111windowcnt++;
    invert_popup_window->invert_popup_window->show();
};


void home::on_grayscale_click(){
    if(curr_image==NULL){dialog("Please Open an Image First."); on_open_click();return;}

    if(is_window_open){dialog("Please close previously opened windows first.");return;}

    set_opacity(OPACITY_IN_1);

    curr_image=colortogray(curr_image,height,width);

    set_opacity(OPACITY_OUT);
    if(curr_image==NULL){dialog("Unable to convert Image to Grayscale.");return;}


    /***FILE_HANDLING_COMMON***/

    char outfilename[100];
    sprintf(outfilename,"%s/temp-%d.bmp",location_bin,bin_count);

    FILE*out_file=save_img_to_file(curr_image,height,width,in_file,outfilename);
    if(out_file==NULL){dialog("Sorry! Unable to Invert Image.");return;}
    fclose(in_file);fclose(out_file);
    in_file=fopen(outfilename,"rb+");
    if(in_file==NULL){dialog("Sorry! Unable to Invert Image.");hide();return;}

    /***PREVIEW_HANDLING_COMMON***/

    set_image_preview();

    bin_count++;

    return;
};


void home::on_halftone_click(){
    if(curr_image==NULL){dialog("Please Open an Image First."); on_open_click();return;}

    if(is_window_open){dialog("Please close previously opened windows first.");return;}

    set_opacity(OPACITY_IN_1);

    curr_image=half_tone(curr_image,height,width);

    set_opacity(OPACITY_OUT);

    if(curr_image==NULL){dialog("Unable to Halftone Image.");return;}

    /***FILE_HANDLING_COMMON***/

    char outfilename[100];
    sprintf(outfilename,"%s/temp-%d.bmp",location_bin,bin_count);
    FILE*out_file=save_img_to_file(curr_image,height,width,in_file,outfilename);
    if(out_file==NULL){dialog("Sorry! Unable to Halftone Image.");return;}
    fclose(in_file);fclose(out_file);
    in_file=fopen(outfilename,"rb+");
    if(in_file==NULL){dialog("Sorry! Unable to Halftone Image.");hide();return;}

    /***PREVIEW_HANDLING_COMMON***/

    set_image_preview();

    bin_count++;

    return;

};


void home::on_edge_click(){


    if(curr_image==NULL){dialog("Please Open an Image First."); on_open_click();return;}

    if(is_window_open){dialog("Please close previously opened windows first.");return;}

    set_opacity(OPACITY_IN_1);

    curr_image=edge_detect(curr_image,height,width);

    set_opacity(OPACITY_OUT);
    if(curr_image==NULL){dialog("Unable to Detect Edges.");return;}

    /***FILE_HANDLING_COMMON***/

    char outfilename[100];
    sprintf(outfilename,"%s/temp-%d.bmp",location_bin,bin_count);
    FILE*out_file=save_img_to_file(curr_image,height,width,in_file,outfilename);
    if(out_file==NULL){dialog("Sorry! Unable to Detect Edges.");return;}
    fclose(in_file);fclose(out_file);
    in_file=fopen(outfilename,"rb+");
    if(in_file==NULL){dialog("Sorry! Unable to Detect Edges.");hide();return;}

    /***PREVIEW_HANDLING_COMMON***/

    set_image_preview();

    bin_count++;

    return;


};


void home::on_stretch_click(){


    if(curr_image==NULL){dialog("Please Open an Image First."); on_open_click();return;}

    if(is_window_open){dialog("Please close previously opened windows first.");return;}
    else{is_window_open=true;}

    set_opacity(OPACITY_IN);



    stretch_popup *stretch_popup_window = new stretch_popup;
    stretch_popup_window->stretch_popup_window = new Stretch_Option;
    stretch_popup_window->stretch_popup_window->signal_hide().connect(sigc::bind<stretch_popup*>(sigc::mem_fun(*this, &home::on_stretch_popup_close), stretch_popup_window));

    stretch_popup_window->stretch_popup_window->show();
};


void home::on_blur_click(){
    if(curr_image==NULL){dialog("Please Open an Image First."); on_open_click();return;}

    if(is_window_open){dialog("Please close previously opened windows first.");return;}
    else{is_window_open=true;}

    set_opacity(OPACITY_IN);

    blur_popup *blur_popup_window = new blur_popup;
    blur_popup_window->blur_popup_window = new Enter_Blur_Radius;

    blur_popup_window->blur_popup_window->signal_hide().connect(sigc::bind<blur_popup*>(sigc::mem_fun(*this, &home::on_blur_popup_close), blur_popup_window));

    blur_popup_window->blur_popup_window->show();

};


void home::on_warp_click(){
    if(curr_image==NULL){dialog("Please Open an Image First."); on_open_click();return;}

    if(is_window_open){dialog("Please close previously opened windows first.");return;}
    else{is_window_open=true;}

    set_opacity(OPACITY_IN);

    warp_popup *warp_popup_window = new warp_popup;
    warp_popup_window->warp_popup_window = new Warp_Coordinates;

    warp_popup_window->warp_popup_window->signal_hide().connect(sigc::bind<warp_popup*>(sigc::mem_fun(*this, &home::on_warp_popup_close), warp_popup_window));

    warp_popup_window->warp_popup_window->show();
};


void home::on_contrast_click(){

    if(curr_image==NULL){dialog("Please Open an Image First."); on_open_click();return;}

    if(is_window_open){dialog("Please close previously opened windows first.");return;}

    set_opacity(OPACITY_IN_1);

    curr_image=quick_contrast(curr_image,height,width);

    set_opacity(OPACITY_OUT);

    if(curr_image==NULL){dialog("Unable to Enhance Image Contrast.");return;}

    /***FILE_HANDLING_COMMON***/

    char outfilename[100];
    sprintf(outfilename,"%s/temp-%d.bmp",location_bin,bin_count);
    FILE*out_file=save_img_to_file(curr_image,height,width,in_file,outfilename);
    if(out_file==NULL){dialog("Sorry! Unable to Enhance Image Contrast.");return;}
    fclose(in_file);fclose(out_file);
    in_file=fopen(outfilename,"rb+");
    if(in_file==NULL){dialog("Sorry! Unable to Enhance Image Contrast.");hide();return;}

    /***PREVIEW_HANDLING_COMMON***/

    set_image_preview();

    bin_count++;

    return;

};

void home::on_f1_click(){

    if(curr_image==NULL){dialog("Please Open an Image First."); on_open_click();return;}

    if(is_window_open){dialog("Please close previously opened windows first.");return;}

    set_opacity(OPACITY_IN_1);

    curr_image=dither(curr_image,height,width);

    set_opacity(OPACITY_OUT);

    if(curr_image==NULL){dialog("Unable to Dither Image.");return;}

    /***FILE_HANDLING_COMMON***/

    char outfilename[100];
    sprintf(outfilename,"%s/temp-%d.bmp",location_bin,bin_count);
    FILE*out_file=save_img_to_file(curr_image,height,width,in_file,outfilename);
    if(out_file==NULL){dialog("Sorry! Unable to Dither Image.");return;}
    fclose(in_file);fclose(out_file);
    in_file=fopen(outfilename,"rb+");
    if(in_file==NULL){dialog("Sorry! Unable to Dither Image.");hide();return;}

    /***PREVIEW_HANDLING_COMMON***/

    set_image_preview();

    bin_count++;

    return;

};

void home::on_f2_click(){
    if(curr_image==NULL){dialog("Please Open an Image First."); on_open_click();return;}

    if(is_window_open){dialog("Please close previously opened windows first.");return;}

    set_opacity(OPACITY_IN_1);

    curr_image=sepia(curr_image,height,width);

    set_opacity(OPACITY_OUT);
    if(curr_image==NULL){dialog("Unable to convert Image to Sepia.");return;}


    /***FILE_HANDLING_COMMON***/

    char outfilename[100];
    sprintf(outfilename,"%s/temp-%d.bmp",location_bin,bin_count);
    FILE*out_file=save_img_to_file(curr_image,height,width,in_file,outfilename);
    if(out_file==NULL){dialog("Sorry! Unable to convert Image to Sepia.");return;}
    fclose(in_file);fclose(out_file);
    in_file=fopen(outfilename,"rb+");
    if(in_file==NULL){dialog("Sorry! Unable to convert Image to Sepia.");hide();return;}

    /***PREVIEW_HANDLING_COMMON***/

    set_image_preview();

    bin_count++;

    return;
};

void home::on_f3_click(){

    if(curr_image==NULL){dialog("Please Open an Image First."); on_open_click();return;}

    if(is_window_open){dialog("Please close previously opened windows first.");return;}

    set_opacity(OPACITY_IN_1);

    curr_image=enhancecontrast(curr_image,height,width,75);

    set_opacity(OPACITY_OUT);

    if(curr_image==NULL){dialog("Unable to perform iMagik.");return;}

    /***FILE_HANDLING_COMMON***/

    char outfilename[100];
    sprintf(outfilename,"%s/temp-%d.bmp",location_bin,bin_count);
    FILE*out_file=save_img_to_file(curr_image,height,width,in_file,outfilename);
    if(out_file==NULL){dialog("Sorry! Unable to perform iMagik.");return;}
    fclose(in_file);fclose(out_file);
    in_file=fopen(outfilename,"rb+");
    if(in_file==NULL){dialog("Sorry! Unable to perform iMagik.");hide();return;}

    /***PREVIEW_HANDLING_COMMON***/

    set_image_preview();

    bin_count++;

    return;


};

void home::on_f4_click(){
    if(curr_image==NULL){dialog("Please Open an Image First."); on_open_click();return;}

    if(is_window_open){dialog("Please close previously opened windows first.");return;}

    set_opacity(OPACITY_IN_1);

    curr_image=negative(curr_image,height,width);

    set_opacity(OPACITY_OUT);
    if(curr_image==NULL){dialog("Unable to build the Negative.");return;}


    /***FILE_HANDLING_COMMON***/

    char outfilename[100];
    sprintf(outfilename,"%s/temp-%d.bmp",location_bin,bin_count);
    FILE*out_file=save_img_to_file(curr_image,height,width,in_file,outfilename);
    if(out_file==NULL){dialog("Sorry! Unable to build the Negative");return;}
    fclose(in_file);fclose(out_file);
    in_file=fopen(outfilename,"rb+");
    if(in_file==NULL){dialog("Sorry! Unable to build the Negative");hide();return;}

    /***PREVIEW_HANDLING_COMMON***/

    set_image_preview();

    bin_count++;

    return;
};


void home::on_f5_click(){

    if(curr_image==NULL){dialog("Please Open an Image First."); on_open_click();return;}

    if(is_window_open){dialog("Please close previously opened windows first.");return;}
    else{is_window_open=true;}

    set_opacity(OPACITY_IN);

    hue_popup *hue_popup_window = new hue_popup;
    hue_popup_window->hue_popup_window = new Enter_Hue;
    hue_popup_window->hue_popup_window->signal_hide().connect(sigc::bind<hue_popup*>(sigc::mem_fun(*this, &home::on_hue_popup_close), hue_popup_window));

    hue_popup_window->hue_popup_window->show();

    return;

};

void home::on_f6_click(){
    if(curr_image==NULL){dialog("Please Open an Image First."); on_open_click();return;}

    if(is_window_open){dialog("Please close previously opened windows first.");return;}

    set_opacity(OPACITY_IN_1);

    curr_image=salt_pepper(curr_image,height,width);

    set_opacity(OPACITY_OUT);

    if(curr_image==NULL){dialog("Unable to Salt & Pepper.");return;}

    /***FILE_HANDLING_COMMON***/

    char outfilename[100];
    sprintf(outfilename,"%s/temp-%d.bmp",location_bin,bin_count);
    FILE*out_file=save_img_to_file(curr_image,height,width,in_file,outfilename);
    if(out_file==NULL){dialog("Sorry! Unable to Salt & Pepper.");return;}
    fclose(in_file);fclose(out_file);
    in_file=fopen(outfilename,"rb+");
    if(in_file==NULL){dialog("Sorry! Unable to Salt & Pepper.");hide();return;}

    /***PREVIEW_HANDLING_COMMON***/

    set_image_preview();

    bin_count++;

    return;
};


void home::on_f7_click(){

};


void home::on_f8_click(){
   if(curr_image==NULL){dialog("Please Open an Image First."); on_open_click();return;}

    if(is_window_open){dialog("Please close previously opened windows first.");return;}
    else{is_window_open=true;}

    set_opacity(OPACITY_IN);

    qblur_popup *qblur_popup_window = new qblur_popup;
    qblur_popup_window->qblur_popup_window = new Enter_qblur_Radius;
    qblur_popup_window->qblur_popup_window->signal_hide().connect(sigc::bind<qblur_popup*>(sigc::mem_fun(*this, &home::on_qblur_popup_close), qblur_popup_window));

    qblur_popup_window->qblur_popup_window->show();
};

void home::on_f9_click(){


    if(curr_image==NULL){dialog("Please Open an Image First."); on_open_click();return;}

    if(is_window_open){dialog("You cannot open multiple windows.");return;}
    else{is_window_open=true;}

    char inputfile[200]="\0",short_fname[100];

    set_opacity(OPACITY_IN);

    Gtk::FileChooserDialog fcdialog("Open image",
	                              Gtk::FILE_CHOOSER_ACTION_OPEN);
	fcdialog.add_button (Gtk::Stock::OPEN,
	                   Gtk::RESPONSE_ACCEPT);
	fcdialog.add_button (Gtk::Stock::CANCEL,
	                   Gtk::RESPONSE_CANCEL);

	Glib::RefPtr<Gtk::FileFilter> filter =
		Gtk::FileFilter::create();
	filter->add_pixbuf_formats();
	filter->set_name("Images");
	fcdialog.add_filter (filter);

	const int response = fcdialog.run();
	fcdialog.hide();

	is_window_open=false;

	switch (response)
	{
		case Gtk::RESPONSE_ACCEPT:
			copy_string0(inputfile,fcdialog.get_filename());
			break;
		default:
			break;
	}

    set_opacity(OPACITY_OUT);

    pixel**wimage=NULL;
    int wheight,wwidth;

    strcpy(short_fname,inputfile);

    if(!change_filename(short_fname)){dialog("Could Not Open Image.");return;}



    wimage=image_pixel_array(inputfile);
    if(wimage==NULL){dialog("Could Not Open Image.");return;}
    wheight=image_height(inputfile);
    wwidth=image_width(inputfile);
    if(wheight==0||wwidth==0){delete[]wimage;return;}

    set_opacity(OPACITY_IN_1);

    curr_image=watermark(curr_image,wimage,height,width,wheight,wwidth);


    set_opacity(OPACITY_OUT);

    if(curr_image==NULL){dialog("Unable to add Watermark.");return;}

    /***FILE_HANDLING_COMMON***/

    char outfilename[100];
    sprintf(outfilename,"%s/temp-%d.bmp",location_bin,bin_count);
    FILE*out_file=save_img_to_file(curr_image,height,width,in_file,outfilename);
    if(out_file==NULL){dialog("Sorry! Unable to add Watermark.");return;}
    fclose(in_file);fclose(out_file);
    in_file=fopen(outfilename,"rb+");
    if(in_file==NULL){dialog("Sorry! Unable to add Watermark.");hide();return;}

    /***PREVIEW_HANDLING_COMMON***/

    set_image_preview();

    bin_count++;

    return;

};



void home::dialog(Glib::ustring msg)
{
    set_opacity(OPACITY_IN);
    Gtk::MessageDialog dlg(msg, false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
    dlg.set_title("Digital Image Processor");
    dlg.run();
    if(!is_window_open){set_opacity(OPACITY_OUT);}
}
