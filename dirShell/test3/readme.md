Input anyone of command bellow:
make DEFINE_VRE=true OPT=define Output: Hello World!
make DEFINE_VRE=true OPT=add Output: Hello World! Kelly!
make DEFINE_VRE=true OPT=recover  Output: Hello World! Again!
make DEFINE_VRE= OPT=define Output: Hello World! First!
make DEFINE_VRE= OPT=add Output: Kelly!
make DEFINE_VRE= OPT=recover Output: Hello World! Again!

Through above example and the conclusion is:
'=' 	Represent basic definition;
':='	Overlay formal value;
'?='	If have been assigned any value then assign the value after '=' to;
'+='	Append the value bellow '=' to current value;

