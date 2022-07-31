#include<iostream>
#include "wpa.h"
using namespace std;

extern "C" {
	#include "CE.h"
	#include "hello.h"
	#include "file1.h"
	#include "file2.h"
}

int main()
{
	wpa();
	CE();
	hello();
	file1();
	file2();
	return 0;
}
