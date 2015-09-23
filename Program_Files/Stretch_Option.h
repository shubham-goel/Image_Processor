#ifndef STRETCH_OPTION_H
#define STRETCH_OPTION_H

#include<gtkmm.h>
class Stretch_Option : public Gtk::Window
{
    public:
        Stretch_Option();
        virtual ~Stretch_Option();
    protected:
        void on_stretch_click(Gtk::Entry *e_x1,Gtk::Entry *e_y1);
        void dialog(Glib::ustring msg);
    private:
};

#endif // STRETCH_OPTION_H
