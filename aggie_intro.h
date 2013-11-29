#ifndef AGGIE_INTRO_GUARD
#define AGGIE_INTRO_GUARD 1

#include "GUI.h"    // for Simple_window only (doesn't really belong in Window.h)
#include "Graph.h"
#include "Window.h"
#include "aggie_snap_window.h"


using namespace Graph_lib;

struct aggie_intro : Graph_lib::Window {
    aggie_intro(Point xy, int w, int h, const string& title );
	
		Image Start;
        Image AggieSnap;
		Text Intro;
        Text Description;
        Text Names;
	
	private:
	
	Button start_button;
	Button continue_button;
        
	void continue_pressed() { hide();  }
	void start_pressed() {detach(Start); detach(start_button); attach(AggieSnap); attach(continue_button); attach(Intro); attach(Description); attach(Names);}   
	static void cb_start_pressed(Address, Address);
	static void cb_continue_pressed(Address, Address);
	
	
	
	
};
#endif // AGGIE_WINDOW_GUARD