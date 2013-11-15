#include "aggie_snap_window.h"

using namespace Graph_lib;

//------------------------------------------------------------------------------

aggie_snap_window::aggie_snap_window(Point xy, int w, int h, const string& title ) 
   :Window(xy,w,h,title),
		
		Intro(Point(350,250),"This program is a photo library."),
		Description(Point(275,270),"It's features include adding and searching pictures."),
		Names(Point(0,590),"Designed by: Alex Benavides, Nathan Barker, Ezequiel Cabezas."),
		
		files_button(Point(0,0),70,20,"Files",cb_files),
		files_menu(Point(0,20),70,20,Menu::vertical,"File"),
		
		search_box(Point(150,5),200,20,"Search:"),
		search_button(Point(360,5),70,20, "Enter", cb_picture_search),
		add_box(Point(150,5),200,20,"Location + File:"),
		add_button(Point(360,5),70,20, "Enter", cb_picture_add),
		add_url_image_box(Point(150,5),200,20,"URL + File:"),
		add_url_image_button(Point(360,5),70,20, "Enter", cb_url_pressed)
		
	{
		files_menu.attach(new Button(Point(0,0),0,0,"Local Add",cb_add));
		files_menu.attach(new Button(Point(0,0),0,0,"Web Add",cb_url_input)); 
		files_menu.attach(new Button(Point(0,0),0,0,"Search",cb_search));
		
		attach(files_menu);
		attach(files_button);
		files_menu.hide();
		
		Intro.set_font_size(20);
		attach(Intro);
		Description.set_font_size(20);
		attach(Description);
		Names.set_font_size(20);
		attach(Names);
		
	}


//------------------------------------------------------------------------------

void aggie_snap_window::cb_add(Address, Address pw)     // "the usual"
{  
    reference_to<aggie_snap_window>(pw).add();
} 

//------------------------------------------------------------------------------

void aggie_snap_window::cb_search(Address, Address pw)     // "the usual"
{  
    reference_to<aggie_snap_window>(pw).search();
} 

//------------------------------------------------------------------------------


void aggie_snap_window::cb_files(Address, Address pw)     // "the usual"
{  
    reference_to<aggie_snap_window>(pw).files_pressed();
} 

//------------------------------------------------------------------------------

void aggie_snap_window::cb_picture_add(Address, Address pw)     // "the usual"
{  
    reference_to<aggie_snap_window>(pw).add_pressed();
} 

//------------------------------------------------------------------------------

void aggie_snap_window::cb_picture_search(Address, Address pw)     // "the usual"
{  
    reference_to<aggie_snap_window>(pw).search_pressed();
} 

//------------------------------------------------------------------------------
void aggie_snap_window::cb_url_input(Address, Address pw)     // "the usual"
{  
    reference_to<aggie_snap_window>(pw).url_input();
} 

//-------------------------------------------------------------------
void aggie_snap_window::cb_url_pressed(Address, Address pw)     // "the usual"
{  
    reference_to<aggie_snap_window>(pw).url_pressed();
} 

//------------------------------------------------------------------------------
