#ifndef HOME_WINDOW_H
#define HOME_WINDOW_H

#include <gtkmm.h>
#include"Enter_Crop_Coordinates.h"
#include"Enter_Angle.h"
#include"Invert_Option.h"
#include"Stretch_Option.h"
#include"Enter_Blur_Radius.h"
#include"Warp_Coordinates.h"
#include"Enter_Hue.h"
#include"Enter_qblur_Radius.h"

#include<stdio.h>
#include<string.h>
#include<math.h>

struct pixel{
    unsigned char red;
    unsigned char green;
    unsigned char blue;

};

struct hsl_pixel{
    unsigned int hue;//0<hue<36000
    unsigned int saturation;//0<saturation<10000
    unsigned int lightness;//0<lightness<10000
};


class home : public Gtk::Window
{
    public:
        home();
        virtual ~home();
    protected:
        void on_open_click();
        void on_exit_click();
        void on_save_click();
        void on_undo_click();
        void on_crop_click();
        void on_rotate_click();
        void on_invert_click();
        void on_grayscale_click();
        void on_halftone_click();
        void on_edge_click();
        void on_stretch_click();
        void on_blur_click();
        void on_warp_click();
        void on_contrast_click();
        void on_f1_click();
        void on_f2_click();
        void on_f3_click();
        void on_f4_click();
        void on_f5_click();
        void on_f6_click();
        void on_f7_click();
        void on_f8_click();
        void on_f9_click();

        void dialog(Glib::ustring msg);

    private:

        Gtk::Image*image;
        pixel **curr_image;
        unsigned int height;
        unsigned int width;
        char original_filename[100];
        Gtk::Label *l_preview_name;
        char current_filename[100];
        char location_input[100];
        char location_output[100];
        char location_bin[100];
        FILE*in_file;
        unsigned int bin_count;
        unsigned int output_count;
        void set_image_preview();

        bool is_window_open;

/**POPUPS**/


        struct crop_popup{
            Enter_Crop_Coordinates *crop_popup_window;
        };
        void on_crop_popup_close(crop_popup *crop_popup_window);
        std::map<int, crop_popup*> popups2;

        struct rotate_popup{
            Enter_Angle *rotate_popup_window;
        };
        void on_rotate_popup_close(rotate_popup *rotate_popup_window);
        std::map<int, rotate_popup*> popups3;

        struct invert_popup{
            Invert_Option *invert_popup_window;
        };
        void on_invert_popup_close(invert_popup *invert_popup_window);
        std::map<int, invert_popup*> popups4;

        struct stretch_popup{
            Stretch_Option *stretch_popup_window;
        };
        void on_stretch_popup_close(stretch_popup *stretch_popup_window);
        std::map<int, stretch_popup*> popups5;

        struct blur_popup{
            Enter_Blur_Radius *blur_popup_window;
        };
        void on_blur_popup_close(blur_popup *blur_popup_window);
        std::map<int, blur_popup*> popups6;

        struct warp_popup{
            Warp_Coordinates *warp_popup_window;
        };
        void on_warp_popup_close(warp_popup *warp_popup_window);
        std::map<int, warp_popup*> popups7;

        struct hue_popup{
            Enter_Hue *hue_popup_window;
        };
        void on_hue_popup_close(hue_popup *hue_popup_window);
        std::map<int, hue_popup*> popups8;

        struct qblur_popup{
            Enter_qblur_Radius *qblur_popup_window;
        };
        void on_qblur_popup_close(qblur_popup *qblur_popup_window);
        std::map<int, qblur_popup*> popups9;

};

#endif // MYWINDOW_H
