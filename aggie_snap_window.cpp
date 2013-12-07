#include "aggie_snap_window.h"

using namespace Graph_lib;

//------------------------------------------------------------------------------

aggie_snap_window::aggie_snap_window(Point xy, int w, int h, const string& title ) 
   :Window(xy,w,h,title),
                
                Url_Error(Point(505,20),"Bad Input. Check the address, tags and there is a name."),
				Tag_Error(Point(505,70),"(only Family Friends Aggieland Pets Vacation. Separated by spaces.)"),
				Tag_Remove_Error(Point(505,70),"(Bad Tag was removed)"),
				eg_tag(Point(505,70),"(e.g. Family Friends Aggieland Pets Vacation)"),							//intro and example text objects
				eg_url(Point(505,20),"(e.g. http://Aggielandrules.com/picture.jpg)"),
				eg_local(Point(505,25),"(e.g. /Pictures/folder1/Reveille.gif)"),
				browser_error(Point(400,250),"No files in library"),
				
                files_button(Point(0,0),70,20,"Files",cb_files),							//menu button
                files_menu(Point(0,20),70,20,Menu::vertical,"File"),
				
				search_box(Point(150,5),200,20,"Search:"),
				search_error(Point(400,250),"Bad Tag Search"),
                search_button(Point(360,5),70,20, "Enter", cb_picture_search),
                add_box(Point(200,5),300,20,"Location + File:"),
                add_button(Point(355,30),70,20, "Enter", cb_picture_add),
				close_add(Point(430,30),70,20, "Close", cb_add_close),
                add_url_image_box(Point(150,5),350,20,"URL + File:"),
                add_url_image_button(Point(355,30),70,20, "Add", cb_url_pressed),
				close_web_add(Point(430,30),70,20, "Close", cb_close_url_add),						//all buttons for program
				tag_box(Point(200,55),300,20, "Add Tags:"),
                name_box(Point(200,30),150,20,"Name your picture:"),
				next_button(Point(900,500),70,20, "Next", cb_next_image),
				previous_button(Point(100,500),70,20, "Previous", cb_previous_image),
				done(Point(450,25),70,20, "Back", cb_done),
				done_error(Point(450,25),70,20, "Back", cb_done_error),
				back_error(Point(450,25),70,20, "Back", cb_error_search),
				back_search(Point(450,25),70,20, "Back", cb_done_search),
				previous_search(Point(100,500),70,20, "Previous", cb_previous_search),
				next_search(Point(900,500),70,20, "Next", cb_next_search)
				
        {
                files_menu.attach(new Button(Point(0,0),0,0,"Local Add",cb_add));
                files_menu.attach(new Button(Point(0,0),0,0,"Web Add",cb_url_input)); 				//attaching menu buttons
                files_menu.attach(new Button(Point(0,0),0,0,"Search",cb_search));
                files_menu.attach(new Button(Point(0,0),0,0,"Browse",cb_browse));
				
				Url_Error.set_font_size(15);
				Url_Error.set_color(Color::red);
				
				Tag_Error.set_font_size(15);
				Tag_Error.set_color(Color::red);							//setting font and color of text objects
                Tag_Remove_Error.set_font_size(15);
				Tag_Remove_Error.set_color(Color::red);
				
				search_error.set_font_size(25);
				search_error.set_color(Color::red);
				eg_tag.set_font_size(15);
				eg_url.set_font_size(15);
				eg_local.set_font_size(15);
				browser_error.set_font_size(25);
				browser_error.set_color(Color::red);
				
				attach(files_menu);
                attach(files_button);
                files_menu.hide();
				
				
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
void aggie_snap_window::cb_add_close(Address, Address pw)     // "the usual"
{  
    reference_to<aggie_snap_window>(pw).add_close();
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

void aggie_snap_window::cb_close_url_add(Address, Address pw)     // "the usual"
{  
    reference_to<aggie_snap_window>(pw).close_url_add();
} 

//------------------------------------------------------------------------------
void aggie_snap_window::cb_browse(Address, Address pw)     // "the usual"
{  
    reference_to<aggie_snap_window>(pw).img_browse();
} 

//------------------------------------------------------------------------------

void aggie_snap_window::cb_next_image(Address, Address pw)     // "the usual"
{  
    reference_to<aggie_snap_window>(pw).next_image();
} 

//------------------------------------------------------------------------------

void aggie_snap_window::cb_previous_image(Address, Address pw)     // "the usual"
{  
    reference_to<aggie_snap_window>(pw).previous_image();
} 

//------------------------------------------------------------------------------

void aggie_snap_window::cb_done(Address, Address pw)     // "the usual"
{  
    reference_to<aggie_snap_window>(pw).done_browse();
} 

//------------------------------------------------------------------------------

void aggie_snap_window::cb_done_error(Address, Address pw)     // "the usual"
{  
    reference_to<aggie_snap_window>(pw).done_browse_error();
} 

//------------------------------------------------------------------------------

void aggie_snap_window::cb_done_search(Address, Address pw)     // "the usual"
{  
    reference_to<aggie_snap_window>(pw).done_search();
} 

//------------------------------------------------------------------------------

void aggie_snap_window::cb_error_search(Address, Address pw)     // "the usual"
{  
    reference_to<aggie_snap_window>(pw).error_search();
} 

//------------------------------------------------------------------------------

void aggie_snap_window::cb_next_search(Address, Address pw)     // "the usual"
{  
    reference_to<aggie_snap_window>(pw).next_search_img();
} 

//------------------------------------------------------------------------------

void aggie_snap_window::cb_previous_search(Address, Address pw)     // "the usual"
{  
    reference_to<aggie_snap_window>(pw).previous_search_img();
} 

//------------------------------------------------------------------------------
