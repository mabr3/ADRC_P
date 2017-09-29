#include <stdio.h>
#include <stdlib.h>

#include "struct.h"

typdef struct Node{
	int nexthop;
	Node * zero;
	Node * one;

}Node;