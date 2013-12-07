#include "std_lib_facilities_3.h"
#include "aggie_snap_window.h"
#include "aggie_intro.h"
#include "Graph.h"

int main()
try{

Point sp(100,100);
aggie_snap_window win(Point(100,100),1000,600,"Aggie Snap");			//creating aggie snap window
aggie_intro intro(sp,1000,600,"Aggie Snap"); 							//creating intro window

return gui_main();
}
catch(exception& e) {
        cerr << "exception: " << e.what() << '\n';
        return 1;
}
catch (...) {
        cerr << "Some exception\n";
        return 2;
}

