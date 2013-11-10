#ifndef AGGIE_WINDOW_GUARD
#define AGGIE_WINDOW_GUARD 1

#include "GUI.h"    // for Simple_window only (doesn't really belong in Window.h)
#include "Graph.h"
#include "Window.h"

using namespace Graph_lib;

//------------------------------------------------------------------------------

struct aggie_snap_window : Graph_lib::Window {
    aggie_snap_window(Point xy, int w, int h, const string& title );
	
	Menu files_menu;
    Button files_button;
	
	Text Intro;
	Text Description;
	Text Names;
	
	In_box add_box;
	Button add_button;
	
	In_box search_box;
	Button search_button;
	
private:

	
	void hide_files() { files_menu.hide();} 
	void files_pressed() { files_button.hide(); files_menu.show(); detach(Intro); detach(Description); detach(Names);}
	void show_in_box() { attach(add_box); attach(add_button);}
	void show_search_box() { attach(search_box); attach(search_button); }
	void add_pressed() { detach(add_box); detach(add_button);  files_button.show(); }
	void search_pressed() { detach(search_box); detach(search_button);  files_button.show(); }
	
	static void cb_add(Address, Address); // callback for add_picture
	static void cb_search(Address, Address); // callback for search_picture
	static void cb_files(Address, Address);
	
	static void cb_picture_search(Address, Address);
	static void cb_picture_add(Address, Address);
	
	void add(){ hide_files(); show_in_box();}
	void search(){ hide_files(); show_search_box();}

	
};

//------------------------------------------------------------------------------

#endif // AGGIE_WINDOW_GUARD
