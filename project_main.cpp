#include "std_lib_facilities_3.h"
#include "aggie_snap_window.h"
#include "Graph.h"

int main()
try{

Point sp(100,100);

aggie_snap_window win(sp,1000,600,"Aggie Snap"); 
               

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

