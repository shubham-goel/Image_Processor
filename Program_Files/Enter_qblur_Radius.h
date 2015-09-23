#ifndef ENTER_QBLUR_RADIUS_H
#define ENTER_QBLUR_RADIUS_H


#include<gtkmm.h>

class Enter_qblur_Radius : public Gtk::Window
{
    public:
        Enter_qblur_Radius();
        virtual ~Enter_qblur_Radius();
    protected:
        void on_qblur_click(Gtk::Entry *e_x1);
        void dialog(Glib::ustring msg);
    private:
};

#endif // ENTER_QBLUR_RADIUS_H
