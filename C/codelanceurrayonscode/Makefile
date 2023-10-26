# Makefile qui permet de lancer les differents choix de compilations selon les tests
CHOICE = default
MAKEFILE = main

ifeq ($(CHOICE), default)
    MAKEFILE = main
endif
ifeq ($(CHOICE), triplets)
    MAKEFILE = triplets
endif
ifeq ($(CHOICE), comparator)
    MAKEFILE = comparator
endif
ifeq ($(CHOICE), readerScene)
    MAKEFILE = readerScene
endif
ifeq ($(CHOICE), raytrace)
    MAKEFILE = raytrace
endif

default:
	$(MAKE) -f Makefile.$(MAKEFILE) 

all:
	$(MAKE) -f Makefile.$(MAKEFILE) all 

clean:
	$(MAKE) -f Makefile.$(MAKEFILE) clean 

mrproper:
	$(MAKE) -f Makefile.$(MAKEFILE) mrproper 

doc:
	$(MAKE) -f Makefile.$(MAKEFILE) -j doc 



