#ifndef AGGIE_INTRO_GUARD
#define AGGIE_INTRO_GUARD 1

#include "GUI.h"    // for Simple_window only (doesn't really belong in Window.h)
#include "Graph.h"
#include "Window.h"
#include "aggie_snap_window.h"

using namespace Graph_lib;

struct aggie_intro : Graph_lib::Window {								//intro slash description window
    aggie_intro(Point xy, int w, int h, const string& title );
	
		Image Start;
        Image AggieSnap;
		Text Intro;							//Image and text objects
        Text Description;
        Text Names;
	
	private:
	
	Button start_button;						//button to pass intro 
	Button continue_button;						//close intro window 
        
	void continue_pressed() { hide();  }				//functions for continue button
	void start_pressed() {detach(Start); detach(start_button); attach(AggieSnap); attach(continue_button); attach(Intro); attach(Description); attach(Names);}     //function for intro button
	static void cb_start_pressed(Address, Address);
	static void cb_continue_pressed(Address, Address);	
};
#endif // AGGIE_WINDOW_GUARD