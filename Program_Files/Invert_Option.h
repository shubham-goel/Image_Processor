#ifndef INVERT_OPTION_H
#define INVERT_OPTION_H

#include<gtkmm.h>

class Invert_Option : public Gtk::Window
{
    public:
        Invert_Option();
        virtual ~Invert_Option();
    protected:
        void on_invert_h_click();
        void on_invert_v_click();
        void dialog(Glib::ustring msg);
    private:
};

#endif // INVERT_OPTION_H
