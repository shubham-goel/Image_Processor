#include <gtkmm.h>

#include "home_window.h"
#include<iostream>

int main(int argc, char *argv[])
{
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "com.DIP.base");
    home window;

    return app->run(window);
}
