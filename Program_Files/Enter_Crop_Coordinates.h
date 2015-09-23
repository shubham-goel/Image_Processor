#ifndef ENTER_CROP_COORDINATES_H
#define ENTER_CROP_COORDINATES_H
#include <gtkmm.h>

class Enter_Crop_Coordinates : public Gtk::Window
{
    public:
        Enter_Crop_Coordinates();
        virtual ~Enter_Crop_Coordinates();
    protected:
        void on_crop_click(Gtk::Entry *e_x1,Gtk::Entry *e_y1,Gtk::Entry *e_x2,Gtk::Entry *e_y2);
        void dialog(Glib::ustring msg);
    private:
};

#endif // ENTER_CROP_COORDINATES_H
