#ifndef WARP_COORDINATES_H
#define WARP_COORDINATES_H

#include<gtkmm.h>

class Warp_Coordinates : public Gtk::Window
{
    public:
        Warp_Coordinates();
        virtual ~Warp_Coordinates();
    protected:
        void on_warp_click_1(Gtk::Entry *e_x1,Gtk::Entry *e_y1,Gtk::Entry *e_x2,Gtk::Entry *e_y2);
        void on_warp_click_2(Gtk::Entry *e_x1,Gtk::Entry *e_y1,Gtk::Entry *e_x2,Gtk::Entry *e_y2);
        void dialog(Glib::ustring msg);
    private:
};

#endif // WARP_COORDINATES_H
