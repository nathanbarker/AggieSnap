#include "aggie_intro.h"

using namespace Graph_lib;

//------------------------------------------------------------------------------

aggie_intro::aggie_intro(Point xy, int w, int h, const string& title ) 
   :Window(xy,w,h,title),
				
				Start(Point(0,0),"Start.jpg"),
				AggieSnap(Point(800,0),"Logo.jpg"),
				Intro(Point(350,250),"This program is a photo library."),								//Buttons and text objects
                Description(Point(275,270),"It's features include adding and searching pictures."),
                Names(Point(0,590),"Designed by: Alex Benavides, Nathan Barker, Ezekiel Cabezas."),
				
				continue_button(Point(450,350),70,20,"Continue ", cb_continue_pressed),
				start_button(Point(0,0),1000,600,"Start ", cb_start_pressed)
				{
				
				Intro.set_font_size(20);
                Description.set_font_size(20);								//attaching and setting font sizes
                Names.set_font_size(20);
				attach(start_button);
				attach(Start);
				
				}
				
//------------------------------------------------------------------------------
 void aggie_intro::cb_start_pressed(Address, Address pw)     // "the usual"
{  
    reference_to<aggie_intro>(pw).start_pressed();
} 
//------------------------------------------------------------------------------
 void aggie_intro::cb_continue_pressed(Address, Address pw)     // "the usual"
{  
    reference_to<aggie_intro>(pw).continue_pressed();
} 
