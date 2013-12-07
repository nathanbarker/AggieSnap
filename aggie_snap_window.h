#ifndef AGGIE_WINDOW_GUARD
#define AGGIE_WINDOW_GUARD 1
#include "GUI.h"    // for Simple_window only (doesn't really belong in Window.h)
#include "Graph.h"
#include "Window.h"
using namespace Graph_lib;

//------------------------------------------------------------------------------

struct aggie_snap_window : Graph_lib::Window {								//program class
    aggie_snap_window(Point xy, int w, int h, const string& title );
        
        Menu files_menu;											//drop down menu
		Button files_button;
        
		Text eg_tag;
		Text eg_url;
		Text eg_local;
		Text search_error;
		Text* tags_display;
		
		Text Url_Error;
		Text Tag_Remove_Error;
		Text Tag_Error;
		
		ofstream output;											//input and output stream for writing and reading index file
        ifstream input;
		
		int count = 0;
		
		ifstream browser;											//input stream to read index file
		Image* display_img;											//image for displaying
		Text browser_error;
        
private:
        In_box add_box;
        Button add_button;
		Button close_add;
		
        In_box add_url_image_box;
        Button add_url_image_button;
        
        In_box search_box;
        Button search_button;
		Button back_search;
		Button back_error;
		Button next_search;
		Button previous_search;
		 
		In_box name_box;
		Button close_web_add;
		In_box tag_box;
		
		Vector< Vector<string> > matrix;									//matrix to hold information of all pictures in library
		Vector< Vector<string> > search_matrix;								//matrix to hold information of searched pictures
		Vector <string> v;												
        Vector <string> transfer;
		vector <int> matches;
		
		Button next_button;													//browse next 
		Button previous_button;												//browse previous
		Button done;
		Button done_error;
		  
        void hide_files() { files_menu.hide();} 							//function to hide menu
        void files_pressed() { files_button.hide(); files_menu.show(); }
        void img_browse() { files_menu.hide(); browse(); }						//function called when the browse menu button is pressed
		void done_browse() { files_menu.show(); detach(*display_img); detach(browser_error); detach(done); detach(previous_button); detach(next_button); detach(*tags_display);}
		void done_browse_error() { files_menu.show(); detach(done_error); detach(browser_error);}
		
		void show_in_box() { attach(add_box); attach(add_button); attach(name_box); attach(close_add); attach(tag_box); attach(eg_tag); attach(eg_local);}
        void show_search_box() { attach(search_box); attach(search_button); }        
		void done_search() { files_menu.show(); detach(back_search); detach(*display_img); detach(*tags_display); detach(previous_search); detach(next_search);}
		void error_search() { files_menu.show(); detach(search_error); detach(back_error);}
		
        void search_pressed() {detach(search_box); detach(search_button); attach(back_error); search_tags(); }                                //function that is called when the search BUTTON is pressed
        void add_pressed() { detach(eg_tag); detach(eg_local); detach(Url_Error); detach(Tag_Error); redraw(); next_local(); }										 //function that is called when the add BUTTON is pressed						 																		                     
		void add_close() { detach(eg_tag); detach(eg_local); detach(Url_Error); detach(Tag_Remove_Error); detach(Tag_Error); detach(add_box); detach(add_button); detach(name_box); detach(close_add); detach(tag_box); files_button.show();	}
		void url_pressed() { detach(eg_tag); detach(eg_url);detach(Url_Error); detach(Tag_Remove_Error); detach(Tag_Error); redraw(); next_url();  } 																//function that is called when the url add BUTTON is pressed
		 
		void show_url_input() { attach(add_url_image_box); attach(add_url_image_button); attach(name_box); attach(close_web_add); attach(tag_box); attach(eg_tag); attach(eg_url); } 																				
		void close_url_add() { files_button.show(); detach(add_url_image_box); detach(add_url_image_button); detach(name_box); detach(close_web_add); detach(tag_box); detach(Url_Error); detach(Tag_Error); detach(eg_tag); detach(eg_url); redraw();}
		
		//call backs for the buttons
		static void cb_browse(Address, Address);								//callback for browse button
        static void cb_add(Address, Address);                                     // callback for add_picture
        static void cb_add_close(Address, Address);
		static void cb_search(Address, Address);                                 // callback for search_picture
        static void cb_files(Address, Address);
        static void cb_url_input(Address, Address);
        static void cb_url_pressed(Address, Address);						
        static void cb_picture_search(Address, Address);
        static void cb_picture_add(Address, Address);
		static void cb_close_url_add(Address, Address); 
        static void cb_next_image(Address, Address);
		static void cb_previous_image(Address, Address);
		static void cb_done(Address, Address);
		static void cb_done_error(Address, Address);
		static void cb_done_search(Address, Address);
		static void cb_next_search(Address, Address);
		static void cb_previous_search(Address, Address);
		static void cb_error_search(Address, Address);
		
        void add(){ hide_files(); show_in_box();}
        void search(){ hide_files(); show_search_box();}
        void url_input() { hide_files(); show_url_input(); }

//-----------------------------------------------------------------------------------------------------------------------------------------------------------
	void next_url()													//function for downloading a picture from the web and storing it 
	{
		string img_name;
		string url;
		string final_url;
		string bgning_string1;
		string bgning_string2;
		string bgning_string3;
		string ending_string;	
		string ending_string2;
		
		url=add_url_image_box.get_string();
		img_name=name_box.get_string();
		if(url != "" || img_name != "" )												//check for input
		{
			bgning_string1=url.substr(0,4);
			bgning_string2=url.substr(0,8);
			bgning_string1=url.substr(0,7);
			ending_string=url.substr(url.size()-4,url.size()-1);
			ending_string2=url.substr(url.size()-5,url.size()-1);
			
			bool check = false;
		
			string tags;
			tags=tag_box.get_string();
			istringstream ss(tags);
			string token;
			v.clear();
			while(ss>>token)
			{
				if(token=="Family" || token=="Friends" || token=="Aggieland" || token=="Pets" || token=="Vacation")	  //check that tags are correct
				{v.push_back(token);}
			}				
			if(	bgning_string1=="http://" || bgning_string2=="https://" || bgning_string3=="www."&&					//check for correct website input 
			   (ending_string==".jpg" || 
				ending_string==".gif" ||
				ending_string==".JPG" ||
				ending_string==".GIF" ||
				ending_string==".bmp" ||
				ending_string==".BMP" ||
				ending_string==".png" ||
				ending_string==".PNG" ||
				ending_string2==".jpeg" ||
				ending_string2==".JPEG")
				&& check == true && v.size()<6)
		
			{
			if(ending_string2==".jpeg" || ending_string2==".JPEG")
			{
				final_url= "wget -O Images/"+img_name+ending_string2+" "+url; 							
			}
			else
			{
				final_url= "wget -O Images/"+img_name+ending_string+" "+url;						//get image
			}
				system(final_url.c_str());
			
				input.open("Library.txt");														//store image information in index file
				string move;
				transfer.clear();
				while(getline(input, move))
				{	
					transfer.push_back(move);
				}
				input.close();	
			
				output.open ("Library.txt");
				int c = 0;
				for(auto i : transfer)
				{
					output<<transfer[c]<<endl;
					++c;
				}
			
				output<<img_name+ending_string;			
				for(auto i=0; i<5; ++i)
				{
					if(i<v.size())
					{
						output<<" "+v[i];
					}
					else
					{
						output<<" x";
					}
				}
				output.close();
			}
			else
			{
				attach(Url_Error);
				attach(Tag_Error);
				redraw();
			}
		}
		else
		{
			attach(Url_Error);
			attach(Tag_Error);
			redraw();
		}
	}
//-------------------------------------------------------------------------------------
    void next_local()											//function for retrieving a picture from a local directory
	{
		string img_name;
		string location;
		string final_location;
		string ending_string;
		string ending_string2;

		location=add_box.get_string();
		img_name=name_box.get_string();
		if(location != "" || img_name != "" )					//check for input
		{
			ending_string=location.substr(location.size()-4,location.size()-1);
			ending_string2=location.substr(location.size()-5,location.size()-1);
			bool check = false;
			string tags;
			tags=tag_box.get_string();
			istringstream ss(tags);
			string token;
			v.clear();
			while(ss>>token)
			{
				v.push_back(token);
			}				
			for(int i = 0; i<v.size(); ++i)
			{
				check=false;
				if(v[i]=="Family" || v[i]=="Friends" || v[i]=="Aggieland" || v[i]=="Pets" || v[i]=="Vacation")					//check tags
				{check=true;}
			} 
		
			if((ending_string==".jpg" || 									//check correct directory input
				ending_string==".gif" ||
				ending_string==".JPG" ||
				ending_string==".GIF" ||
				ending_string==".bmp" ||
				ending_string==".BMP" ||
				ending_string==".png" ||
				ending_string==".PNG" || 
				ending_string2==".jpeg" ||
				ending_string2==".JPEG"
				)
				&& check == true && v.size()<6)
			{
				final_location= "cp ~/"+location+" Images/"+img_name+ending_string;
			
				system(final_location.c_str());							//copy file to the Image folder
			
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
				output<<img_name+ending_string;			//store tags
				for(int i=0; i<5; ++i)
				{
					if(i<v.size())
					{
						output<<" "+v[i];
					}
					else
					{
						output<<" x";
					}
				}
				output.close();
			}
			else
			{
				attach(Url_Error);
				attach(Tag_Error);
				redraw();
			}
		
		}
		else
		{
			attach(Url_Error);
			attach(Tag_Error);
			redraw();
		}
				
	}
//------------------------------------------------------------------------------

	void browse()											//functions for browsing picture by tags
	{
		count = 0;
		matrix.clear();
		string token,tag1, tag2, tag3, tag4, tag5;
		browser.open("Library.txt");
		string test;
		string tag_show ="";
		attach(done_error);
		
		getline(browser, test);								
		if(test == "")										//is index file empty?
		{
			attach(browser_error);
			redraw();
		}
		else
		{
			detach(done_error);									 
			attach(done);
			attach(previous_button);  
			istringstream ss(test);
			ss>>token>>tag1>>tag2>>tag3>>tag4>>tag5;
			do															// get tags
			{
				vector <string> row;
				row.push_back(token);
				if (tag1 != "x")
				{
					row.push_back(tag1);
				}
				if (tag2 != "x")
				{
					row.push_back(tag2);
				}
				if (tag3 != "x")
				{
					row.push_back(tag3);
				}
				if (tag4 != "x")
				{
					row.push_back(tag4);
				}
				if (tag5 != "x")
				{
					row.push_back(tag5);
				}
				matrix.push_back(row);											//place read index files into a matrix 
			}while(browser>>token>>tag1>>tag2>>tag3>>tag4>>tag5);
			browser.close();	
			attach(next_button); 
			if(matrix.size()<2)
			{
			next_button.hide();								
			}
			
			previous_button.hide();
			
			display_img = new Image ( Point(180,100), "Images/"+matrix[0][0] );			//display first image 
			
			if(display_img->get_height() <=401 || display_img->get_width() <=401)			//Check and resize
			{
				display_img->copy(400,400);
			}
			for(int i =1; i<matrix[0].size(); ++i)
				{
					tag_show = tag_show + matrix[count][i]+ ", ";								//display tags
				}
			tags_display = new Text ( Point(350,75), "Tags: "+tag_show);
			tags_display->set_font_size(15);
			attach(*tags_display);
		
			attach(*display_img);
			redraw();
		}
	}	
//-----------------------------------------------------------------------------------------------------------------------------------------------------------	
	void next_image()												//display next image 
	{
		string tag_show;
		detach(*tags_display);
		++count;
		if(count >= matrix.size()-1)								
		{
			next_button.hide();
		}
		if(count >= 0)
		{
			previous_button.show();
		}
		detach(*display_img);
		display_img = new Image ( Point(180,100), "Images/"+matrix[count][0]);			//iterate through matrix and display next image
		if(display_img->get_height() <=401 || display_img->get_width() <=401)			//Check and resize
		{
			display_img->copy(400,400);
		}
		
		attach(*display_img);
		
		for(int i =1; i<matrix[count].size(); ++i)
			{
				tag_show = tag_show + matrix[count][i]+ ", ";							//display tags
			}
		tags_display = new Text ( Point(350,75), "Tags: "+tag_show);
		tags_display->set_font_size(15);
		attach(*tags_display);	
		redraw();
	}
	
//-----------------------------------------------------------------------------------------------------
	void previous_image()
	{
		string tag_show = "";
		detach(*tags_display);
		--count;
		if(count <= 0)
		{
			previous_button.hide();
		}
		if(count <= matrix.size()-1)
		{
			next_button.show();
		}
		detach(*display_img);
		display_img = new Image ( Point(180,100), "Images/"+matrix[count][0]);
		if(display_img->get_height() <=401 || display_img->get_width() <=401)					//Check and resize
		{
			display_img->copy(400,400);
		}
		attach(*display_img);
		
		for(int i = 1; i < matrix[count].size(); ++i)
			{
				tag_show = tag_show + matrix[count][i]+ ", ";									//de-increment count adn display previous image 
			}
		tags_display = new Text ( Point(350,75), "Tags: "+tag_show);
		tags_display->set_font_size(15);
		attach(*tags_display);
		redraw();
	}

//-----------------------------------------------------------------------------------------------------	
	
	void search_tags()																//search through images by searched tags
	{
		string search;
		vector <string> tags_searched;
		search=search_box.get_string();
		istringstream ss(search);
		string token = "";
		matches.clear();
		search_matrix.clear();
		tags_searched.clear();														
		string add = "";
		count = 0;

		if(search != "")
		{
			attach(back_search);
			detach(back_error);
			while(ss>>token)
			{
				if(token == "Family" || token == "Friends" || token =="Vacation" || token =="Aggieland" || token =="Pets" && tags_searched.size() <=5)
					{
					tags_searched.push_back(token);
					}
				if( tags_searched.size() > 0 )
					{
						
						count = 0;
						string file,tag1, tag2, tag3, tag4, tag5;
						browser.open("Library.txt");
						string test;
						string tag_show ="";
						
						getline(browser, test);
						if(test == "")
						{
							attach(search_error);
							redraw();
							browser.close();
						}
						else
						{
							istringstream ss(test);
							ss>>file>>tag1>>tag2>>tag3>>tag4>>tag5;
							do
							{	
								vector <string> row;
								row.push_back(file);	
								row.push_back(tag1);					
								row.push_back(tag2);						
								row.push_back(tag3);														
								row.push_back(tag4);										
								row.push_back(tag5);	
								search_matrix.push_back(row);											//put picture info into a matrix
							}while(browser>>file>>tag1>>tag2>>tag3>>tag4>>tag5);
							for(int ii = 0; ii<search_matrix.size(); ++ii)
							{
								for(int i = 0; i<tags_searched.size(); ++i)							
								{
									if(search_matrix[ii][1] == tags_searched[i] || 
										search_matrix[ii][2] == tags_searched[i] ||
										search_matrix[ii][3] == tags_searched[i] ||
										search_matrix[ii][4] == tags_searched[i] ||
										search_matrix[ii][5] == tags_searched[i] )
									{
										matches.push_back(ii);							//searched for matches and place the location in a vector
									}
								}
							}	
								browser.close();
								attach(previous_search);
								previous_search.hide();
								attach(next_search);
								if(matches.size()<=1)
								{
								next_search.hide();
								}
								display_img = new Image ( Point(180,100), "Images/"+search_matrix[matches[0]][0] );				//display first matched picture
								if(display_img->get_height() <=401 || display_img->get_width() <=401)							//Check and resize
									{
										display_img->copy(400,400);
									}
								for(int i =1; i<search_matrix[matches[0]].size(); ++i)
									{
										if(search_matrix[matches[0]][i] != "x")
										{
										tag_show = tag_show + search_matrix[matches[0]][i]+ ", ";
										}
									}
								tags_display = new Text ( Point(350,75), "Tags: "+tag_show);					//display tags
								tags_display->set_font_size(15);
								attach(*tags_display);
							
								attach(*display_img);
								redraw();
						}
					}
				else
					{
						detach(back_search);
						attach(back_error);
						attach(search_error);
					}
			}
		}
		else
			{
				attach(search_error);
			}	
	}			
//-----------------------------------------------------------------------------------------------------
void next_search_img()						//display next image of searched tags
	{
		string tag_show;
		detach(*tags_display);
		++count;
		if(count >= matches.size()-1)
		{
			next_search.hide();
		}
		if(count >= 0)
		{
			previous_search.show();
		}
		detach(*display_img);
		display_img = new Image ( Point(180,100), "Images/"+search_matrix[matches[count]][0]);					//increment count and iterate through matrix to display image
		if(display_img->get_height() <=401 || display_img->get_width() <=401)							//Check and resize
		{
			display_img->copy(400,400);
		}
		attach(*display_img);
		for(int i =1; i<search_matrix[count].size(); ++i)
			{
				if(search_matrix[matches[count]][i] != "x")
				{
				tag_show = tag_show + search_matrix[matches[count]][i]+ ", ";							//display tags
				}
			}
		tags_display = new Text ( Point(350,75), "Tags: "+tag_show);
		tags_display->set_font_size(15);
		attach(*tags_display);
		redraw();
	}	
//-----------------------------------------------------------------------------------------------------	

void previous_search_img()								//display previous image of searched tags
{
		string tag_show;
		detach(*tags_display);
		--count;
		if(count <= matches.size()-1)
		{
			next_search.show();
		}
		if(count <= 0)
		{
			previous_search.hide();
		}
		detach(*display_img);
		display_img = new Image ( Point(180,100), "Images/"+search_matrix[matches[count]][0]);				//de-increment count and display previous image
		if(display_img->get_height() <=251 || display_img->get_width() <=251)							//Check and resize
		{
			display_img->copy(250,250);
		}
		attach(*display_img);
		for(int i =1; i<search_matrix[count].size(); ++i)
			{
				if(search_matrix[matches[count]][i] != "x")
				{
				tag_show = tag_show + search_matrix[matches[count]][i]+ ", ";						//display tags
				}
			}
		tags_display = new Text ( Point(350,75), "Tags: "+tag_show);
		tags_display->set_font_size(15);
		attach(*tags_display);
		redraw();
}
//-----------------------------------------------------------------------------------------------------
};
#endif // AGGIE_WINDOW_GUARD
