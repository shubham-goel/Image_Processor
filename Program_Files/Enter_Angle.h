#ifndef ENTER_ANGLE_H
#define ENTER_ANGLE_H

#include<gtkmm.h>

class Enter_Angle : public Gtk::Window
{
    public:
        Enter_Angle();
        virtual ~Enter_Angle();
    protected:
        void on_rotate_click(Gtk::Entry *eangle);
        void dialog(Glib::ustring msg);
    private:
};

#endif // ENTER_ANGLE_H
