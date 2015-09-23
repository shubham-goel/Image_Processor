#ifndef ENTER_HUE_H
#define ENTER_HUE_H


#include<gtkmm.h>

class Enter_Hue : public Gtk::Window
{
    public:
        Enter_Hue();
        virtual ~Enter_Hue();
    protected:
        void on_hue_click(Gtk::Entry *eHue);
        void dialog(Glib::ustring msg);
    private:
};

#endif // ENTER_HUE_H
