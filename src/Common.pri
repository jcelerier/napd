QMAKE_CXXFLAGS += -std=c++1y 
QMAKE_CXXFLAGS += -Wall -Wextra  -Winit-self -Wparentheses -Wunreachable-code -Wunused -Wunused-function -Wunused-label -Wunused-parameter -Wunused-value -Wunused-variable -Wnon-virtual-dtor -Wreorder -Wstrict-null-sentinel -Wold-style-cast -Wno-non-template-friend  -Woverloaded-virtual -Wno-pmf-conversions -Wsign-promo -Waddress -Waggregate-return -Warray-bounds -Wno-attributes -Wno-builtin-macro-redefined -Wcast-align -Wcast-qual -Wchar-subscripts  -Wclobbered -Wcomment -Wcoverage-mismatch -Wno-deprecated -Wno-deprecated-declarations -Wdisabled-optimization -Wno-div-by-zero -Wempty-body -Wenum-compare -Wno-endif-labels -Wfatal-errors  -Wformat=2 -Wignored-qualifiers -Winit-self -Winline -Wno-int-to-pointer-cast -Wno-invalid-offsetof -Winvalid-pch -Wunsafe-loop-optimizations -Wlogical-op -Wmain -Wmissing-braces -Wmissing-field-initializers -Wmissing-format-attribute -Wmissing-include-dirs -Wmissing-noreturn -Wnonnull -Wno-multichar -Wnonnull -Wno-overflow -Woverlength-strings -Wpacked -Wpacked-bitfield-compat -Wparentheses -Wpointer-arith -Wredundant-decls -Wreturn-type -Wsequence-point  -Wshadow -Wsign-compare -Wstack-protector  -Wstrict-overflow=5 -Wswitch -Wswitch-enum -Wsync-nand  -Wtrigraphs -Wtype-limits -Wuninitialized  -Wvariadic-macros -Wvla -Wvolatile-register-var -Wwrite-strings


QMAKE_CXXFLAGS_RELEASE -= -O0
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3 -flto
QMAKE_LFLAGS_RELEASE   += -O3 -flto
