#include <iostream>
#include "func_map.h"

using namespace std;




//call every module's start function here!
BEGIN_FUNC_MAP()
	RUN_FUNC_IF(false,start_icpc2014)
	RUN_FUNC_IF(false,do_prime_test)
	RUN_FUNC_IF(true,start_heartlove_proberbility)
	RUN_FUNC_IF(false,start_leecode_p218)
	RUN_FUNC_IF(false,start_linecover)
	RUN_FUNC_IF(false,start_leecode_p179_bignum)
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
