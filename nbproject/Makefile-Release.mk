#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/lib/String/String.o \
	${OBJECTDIR}/lib/String/TokenString.o \
	${OBJECTDIR}/lib/fs/Uci/Uci.o \
	${OBJECTDIR}/lib/fs/Uci/UciSection.o \
	${OBJECTDIR}/test/main.o \
	${OBJECTDIR}/test/string_test.o \
	${OBJECTDIR}/test/uci_cmd_test.o \
	${OBJECTDIR}/test/uci_test.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libembedded

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libembedded: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libembedded ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/lib/String/String.o: lib/String/String.cpp
	${MKDIR} -p ${OBJECTDIR}/lib/String
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/String/String.o lib/String/String.cpp

${OBJECTDIR}/lib/String/TokenString.o: lib/String/TokenString.cpp
	${MKDIR} -p ${OBJECTDIR}/lib/String
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/String/TokenString.o lib/String/TokenString.cpp

${OBJECTDIR}/lib/fs/Uci/Uci.o: lib/fs/Uci/Uci.cpp
	${MKDIR} -p ${OBJECTDIR}/lib/fs/Uci
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/fs/Uci/Uci.o lib/fs/Uci/Uci.cpp

${OBJECTDIR}/lib/fs/Uci/UciSection.o: lib/fs/Uci/UciSection.cpp
	${MKDIR} -p ${OBJECTDIR}/lib/fs/Uci
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib/fs/Uci/UciSection.o lib/fs/Uci/UciSection.cpp

${OBJECTDIR}/test/main.o: test/main.cpp
	${MKDIR} -p ${OBJECTDIR}/test
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/test/main.o test/main.cpp

${OBJECTDIR}/test/string_test.o: test/string_test.cpp
	${MKDIR} -p ${OBJECTDIR}/test
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/test/string_test.o test/string_test.cpp

${OBJECTDIR}/test/uci_cmd_test.o: test/uci_cmd_test.cpp
	${MKDIR} -p ${OBJECTDIR}/test
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/test/uci_cmd_test.o test/uci_cmd_test.cpp

${OBJECTDIR}/test/uci_test.o: test/uci_test.cpp
	${MKDIR} -p ${OBJECTDIR}/test
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/test/uci_test.o test/uci_test.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
