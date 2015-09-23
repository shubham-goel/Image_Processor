#ifndef ENTER_BLUR_RADIUS_H
#define ENTER_BLUR_RADIUS_H

#include<gtkmm.h>

class Enter_Blur_Radius : public Gtk::Window
{
    public:
        Enter_Blur_Radius();
        virtual ~Enter_Blur_Radius();
    protected:
        void on_blur_click(Gtk::Entry *e_x1);
        void dialog(Glib::ustring msg);
    private:
};

#endif // ENTER_BLUR_RADIUS_H
