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
		Text Url_Error;
		Text Tag_Error;
		
		
		ofstream output;
        ifstream input;
        
private:
        In_box add_box;
        Button add_button;
        
        In_box add_url_image_box;
        Button add_url_image_button;
        
        In_box search_box;
        Button search_button;
		
		In_box name_box;
		Button close_web_add;
		In_box tag_box;
		
		Vector <string> v;
        Vector <string> transfer;
		
        void hide_files() { files_menu.hide();} 
        void files_pressed() { files_button.hide(); files_menu.show(); detach(Intro); detach(Description); detach(Names);}
        
		void show_in_box() { attach(add_box); attach(add_button);}
        void show_search_box() { attach(search_box); attach(search_button); }        
                     
        void search_pressed() {detach(search_box); detach(search_button); files_button.show();}                                //function that is called when the search BUTTON is pressed
        void add_pressed() { detach(add_box); 																				   //function that is called when the add BUTTON is pressed
							 detach(add_button);
							 files_button.show();
							 //string file = add_box.get_string();
							 //ostringstream os;
						     //os << file;
							 //v.push_back(os.str());				
							}                   
		void url_pressed() { detach(Url_Error); detach(Tag_Error); redraw(); next_url(); } 																//function that is called when the url add BUTTON is pressed
		 
		void show_url_input() { attach(add_url_image_box); attach(add_url_image_button); attach(name_box); attach(close_web_add); attach(tag_box); } 																				
		void close_url_add() { files_button.show(); detach(add_url_image_box); detach(add_url_image_button); detach(name_box); detach(close_web_add); detach(tag_box); detach(Url_Error); detach(Tag_Error);redraw();}
		
	
		
        static void cb_add(Address, Address);                                         // callback for add_picture
        static void cb_search(Address, Address);                                 // callback for search_picture
        static void cb_files(Address, Address);
        static void cb_url_input(Address, Address);
        static void cb_url_pressed(Address, Address);
        static void cb_picture_search(Address, Address);
        static void cb_picture_add(Address, Address);
		static void cb_close_url_add(Address, Address);
        
        void add(){ hide_files(); show_in_box();}
        void search(){ hide_files(); show_search_box();}
        void url_input() { hide_files(); show_url_input(); }
		
//-----------------------------------------------------------------------------
		void next_url()
		{
				string img_name;
				string url;
				string final_url;
				string bgning_string;
				string ending_string;	
	
			url=add_url_image_box.get_string();

			bgning_string=url.substr(0,7);
			ending_string=url.substr(url.size()-4,url.size()-1);
	
	
			img_name=name_box.get_string();

			bool check = false;
			
			string tags;
			tags=tag_box.get_string();
			istringstream ss(tags);
			string token;
			v.clear();
			while(getline(ss, token, ','))
				{
					v.push_back(token);
				}				
			for(int i = 0; i<v.size(); ++i)
				{
				check=false;
					if(v[i]=="Family" ||
						v[i]=="Friends" ||
						v[i]=="Aggieland" ||
						v[i]=="Pets" ||
						v[i]=="Vacation")
					{check=true;}
				} 
		if(bgning_string=="http://" &&			
			(ending_string==".jpg" || 
			ending_string==".gif" ||
			ending_string==".JPG" ||
			ending_string==".GIF" ||
			ending_string==".jpeg"||			
			ending_string==".JPEG" )
			&& check == true && v.size()<6)
			
	    {
			final_url= "wget "+url+" -O "+img_name+".jpg";
			
		
			
			system(final_url.c_str());
			
			input.open("Library.txt");
			string move;
			transfer.clear();
			while(getline(input, move))
				{	
						transfer.push_back(move);
				}
			input.close();	
			
			output.open ("Library.txt");
			
			for(int i=0; i<transfer.size(); ++i)
				{
					output<<transfer[i]<<endl;
				}
			
			output<<"("+img_name+".jpg";			//Family, Friends, Aggieland, Pets, Vacation
			for(int i=0; i<v.size(); ++i)
				{
				output<<","+v[i];
				}
			output<<")";
			output.close();
		}
		else
		{
			attach(Url_Error);
			attach(Tag_Error);
			redraw();
		}

}
//-------------------------------------------------------------------------------------
        
};

//------------------------------------------------------------------------------

#endif // AGGIE_WINDOW_GUARD
