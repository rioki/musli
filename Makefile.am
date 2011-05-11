

pkginclude_HEADERS          = musli/Factorlet.h     musli/MemoryPacker.h   \
                              musli/Packer.h        musli/StreamUnpacker.h \
                              musli/Factory.h       musli/MemoryUnpacker.h \
                              musli/StreamPacker.h  musli/Unpacker.h


lib_LTLIBRARIES             = libmusli.la

libmusli_la_SOURCES         = musli/Factorlet.cpp     musli/MemoryPacker.cpp   \
                              musli/Packer.cpp        musli/StreamUnpacker.cpp \
                              musli/Factory.cpp       musli/MemoryUnpacker.cpp \
                              musli/StreamPacker.cpp  musli/Unpacker.cpp

check_PROGRAMS              = musli_test

musli_test_CXXFLAGS         = -I$(srcdir)/musli
musli_test_LDADD            = libmusli.la $(UNITTEST_LIBS)
musli_test_SOURCES          = musli_test/main.cpp                  \
                              musli_test/CyclicReferencesTest.cpp  \
                              musli_test/PolymorphicObjects.cpp    \
                              musli_test/StreamPackerTest.cpp      \
                              musli_test/SimpleObjectTest.cpp      \
                              musli_test/MemoryPackerTest.cpp      \
                              musli_test/StdContainersTest.cpp

TESTS                       = $(check_PROGRAMS)

EXTRA_DIST                  = README.md COPYING.txt


