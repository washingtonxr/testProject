ifdef DEFINE_VRE
    VRE = “Hello World!”
else
endif

ifeq ($(OPT),define)
    VRE ?= “Hello World! First!”
endif

ifeq ($(OPT),add)
    VRE += “Kelly!”
endif

ifeq ($(OPT),recover)
    VRE := “Hello World! Again!”
endif

all:
    @echo $(VRE)


