#include <iostream>
#include "func_map.h"

using namespace std;




//call every module's start function here!
BEGIN_FUNC_MAP()
	FUNC_ITEM_IF(false,start_icpc2014)
	FUNC_ITEM_IF(true,do_prime_test)
END_FUNC_MAP()


static void init() {
	// call function map
	CALL_FUNC_MAP();


}
int main() {
	//start_modules(); //run modules.
	init();
	return 0;
}
