
#---------- definitions of compiler, suffixes, and options ----------

OS         := $(shell uname )
PLATFORM     := $(shell uname -p)

# Define Suffixes
ObjSuf = o
SrcSuf = cxx
HdrSuf = h
ExeSuf =
DllSuf = so
OutPutOpt = -o 


ifeq ($(OS),Darwin)
DllSuf        = dylib
CXX           = g++
CXXFLAGS      = -02 -pipe -Wall -W -Woverloaded-virtual
LD            = g++
LDFLAGS       = -O2
SOFLAGS       = -m64 -dynamiclib -single_module -undefined dynamic_lookup
endif
ifeq(,$(findstring Linux, $(ARCH)))
DllSuf        = so
CXX           = g++
CXXFLAGS      = -O2 -Wall -Wno-unused-variable -fPIC
LD            = g++
LDFLAGS       = -O2
SOFLAGS       = -shared
endif



ifneq ($(ALTCXX),)
CXX = $(ALTCXX)
endif
ifneq ($(ALTLD),)
LD  = $(ALTLD)
endif


# Paths and Libraries for LibOne
ExampleCFLAGS   := ...
ExampleLDFLAGS  := ...
ExampleLIBS     := ...
ExampleLIBS     += ...
ExampleGLIBS    := ...
HASTHREAD      := ...


#---------- Program sections and variable settings ----------

#Define the sections of the program which get their own libraries and their variable settings

#defines where to find executable files
EXECDIR = src 
#defines where to PUT header files (not where to find them)
INCDIR   = include 
#defines where to put binary files
BINDIR   = bin
#defines where to put library files
LIBDIR   = lib
#defines where to put documentation
HTMLDIR  = doc/html
#defines where the documentation directory is at
DOCDIR = doc

GENDIRS = $(EXECDIR) $(INCDIR) $(BINDIR) $(HTMLDIR)
LIBDIRS = DirectoryOne DirectoryTwo

DIRSECTIONS  = $(OBJDIR) $(LIBDIR) $(BINDIR) $(HTMLDIR)
INCSECTIONS  = TOrcaRootHeader KFPD KIPE Processors Filters Analysis User
LIBSECTIONS  = TOrcaRootHeader KFPD KIPE Processors Filters Analysis User
DICTSECTIONS = TOrcaRootHeader KFPD KIPE Filters Analysis User
EXESECTIONS  = $(notdir $(basename $(wildcard $(SRCDIR)/Main/*.$(SrcSuf))))

$(foreach SECT,$(INCSECTIONS),$(eval CXXFLAGS += -I./$$(SRCDIR)/$(SECT)/$$(INCDIR)))

MYLIBS        = -L./$(LIBDIR)
$(foreach SECT,$(LIBSECTIONS),$(eval MYLIBS += -l$(SECT)))

CXXFLAGS     += $(ROOTCFLAGS) $(ORCFLAGS) -I. -I./include -g
LDFLAGS      += $(ROOTLDFLAGS)
LIBS          = $(ROOTLIBS) $(ORLIBS)

#---------- actual make 'rules' ----------

#macro to define rules for each section of the program
.PHONY: all
all: $(DIRSECTIONS) $(foreach SECT,$(DICTSECTIONS),$(addsuffix _dict,$(SECT))) $(LIBSECTIONS) $(EXESECTIONS)

define DICTSECTION_RULE
.PHONY: $(1)_dict
$(1)DICTOBJ = $$(addprefix $$(OBJDIR)/,$$(addsuffix Dict.$$(ObjSuf),$(1)))
$(1)_dict: $$(addprefix $$(SRCDIR)/$(1)/$$(LINKDEF)/,$$(addsuffix Dict.$$(SrcSuf),$(1)))
endef

define LIBSECTION_RULE
.PHONY: $(1)
$(1): $(OBJDIR) $(LIBDIR) $$(LIBDIR)/lib$(1).$$(DllSuf)
endef

define EXESECTION_RULE
.PHONY: $(1)
$(1): $(BINDIR) $(LIBSECTIONS) $$(addsuffix $$(ExeSuf),$$(addprefix $$(BINDIR)/,$(1)))
endef

$(foreach SECT,$(DICTSECTIONS),$(eval $(call DICTSECTION_RULE,$(SECT))))

$(foreach SECT,$(LIBSECTIONS),$(eval $(call LIBSECTION_RULE,$(SECT))))

$(foreach SECT,$(EXESECTIONS),$(eval $(call EXESECTION_RULE,$(SECT))))

#macro to define rules for creating a directory
define DIRECTORY_RULE
$(1) : 
ifneq (exists, $$(shell [ -d $(1)/ ] ) && echo exists )
	@echo Creating directory $$@...
	@mkdir $(1)
endif
endef

$(foreach SECT,$(DIRSECTIONS),$(eval $(call DIRECTORY_RULE,$(SECT))))

#macro to define rules for creating a section's dictionary
define DICTIONARY_RULE
$$(SRCDIR)/$(1)/$$(LINKDEF)/$(1)Dict.$$(SrcSuf) : $$(wildcard $$(SRCDIR)/$(1)/include/*.$$(HdrSuf)) $$(SRCDIR)/$(1)/$$(LINKDEF)/$(1)LinkDef.$$(HdrSuf)
	@echo Generating dictionary $$@...
	@rootcint -f $$@ -c  -I$$(SRCDIR)/TOrcaRootHeader/include -I$$(SRCDIR)/KFPD/include -I$$(SRCDIR)/KIPE/include -I$$(SRCDIR)/KCAL/include -I$$(SRCDIR)/Analysis/include -I$$(SRCDIR)/Filters/include -I$$(SRCDIR)/User/include $$^
endef

$(foreach SECT,$(DICTSECTIONS),$(eval $(call DICTIONARY_RULE,$(SECT))))

#macro to define rules for creating a section's library
define LIBRARY_RULE
$$(LIBDIR)/lib$(1).$$(DllSuf) : $$(addprefix $$(OBJDIR)/,$$(addsuffix .$$(ObjSuf),$$(notdir $$(basename $$(wildcard $$(SRCDIR)/$(1)/src/*$$(SrcSuf)))))) $$($(1)DICTOBJ)
	@echo -n creating library $$@...
ifeq ($$(ARCH),aix)
		@/usr/ibmcxx/bin/makeC++SharedLib $$(OutPutOpt) $$@ $$(LIBS) -p 0 $$^
else
ifeq ($$(ARCH),aix5)
		@/usr/vacpp/bin/makeC++SharedLib $$(OutPutOpt) $$@ $$(LIBS) -p 0 $$^
else
ifeq ($$(PLATFORM),macosx)
# We need to make both the .dylib and the .so
		@$$(LD) $$(LDFLAGS) $$(SOFLAGS) $$^ $$(OutPutOpt) $$@
ifneq ($$(subst $$(MACOSX_MINOR),,1234),1234)
ifeq ($$(MACOSX_MINOR),4)
		@ln -sf $$@ $(subst .$$(DllSuf),.so,$$@)
else
		@$$(LD) -bundle -undefined $$(UNDEFOPT) $$(LDFLAGS) $$^ \
		   $$(OutPutOpt) $$(subst .$$(DllSuf),.so,$$@)
endif
endif
else
ifeq ($$(PLATFORM),win32)
		bindexplib $$* $$^ > $$*.def
		lib -nologo -MACHINE:IX86 $$^ -def:$$*.def \
		   $$(OutPutOpt)$$(LIBDIR)/lib$(1).$$(DllSuf)
		$$(LD) $$(SOFLAGS) $$(LDFLAGS) $$^ $$*.exp $$(LIBS) \
		   $$(OutPutOpt)$$@
		$$(MT_DLL)
else
		@$$(LD) $$(SOFLAGS) $$(LDFLAGS) $$^ $$(OutPutOpt) $$@ $$(EXPLLINKLIBS)
endif
endif
endif
endif
		@echo " done."

$$(OBJDIR)/%.$$(ObjSuf) : $$(SRCDIR)/$(1)/src/%.$$(SrcSuf)
	@echo compiling $$@...
	@$$(CXX) $$(CXXFLAGS) -c $$< -o $$@

$$(OBJDIR)/%.$$(ObjSuf) : $$(SRCDIR)/$(1)/LinkDef/%.$$(SrcSuf)
	@echo compiling $$@...
	@$$(CXX) $$(CXXFLAGS) -c $$< -o $$@
endef


$(foreach SECT,$(LIBSECTIONS),$(eval $(call LIBRARY_RULE,$(SECT))))

$$(OBJDIR)/%_MPI.$$(ObjSuf) : $$(SRCDIR)/$(1)/src/%.$$(SrcSuf)
	@echo compiling $$@ with MPI compiler...
	@$$(CXX_MPI) $$(CXXFLAGS_MPI) -c $$< -o $$@

$$(OBJDIR)/%_MPI.$$(ObjSuf) : $$(SRCDIR)/$(1)/LinkDef/%.$$(SrcSuf)
	@echo compiling $$@ with MPI compiler...
	@$$(CXX_MPI) $$(CXXFLAGS_MPI) -c $$< -o $$@

#macro to define rules for creating a section's executable
define EXECUTABLE_RULE
$$(BINDIR)/$(1)$$(ExeSuf) : $$(addprefix $$(OBJDIR)/,$$(addsuffix .$(ObjSuf),$(1)))
	@echo -n creating executable $$@...
	@$$(LD) $$(LDFLAGS) $$(LIBS) $$(MYLIBS) $$^  -o $$@
	@echo " done."
endef

$(foreach SECT,$(EXESECTIONS),$(eval $(call EXECUTABLE_RULE,$(SECT))))

#rule for creating the object files for the test programs
$(OBJDIR)/%.$(ObjSuf) : $(SRCDIR)/Main/%.$(SrcSuf)
	@echo compiling $@...
	@$(CXX) $(CXXFLAGS) -c $< -o $@

#rules for generating documentation
.PHONY:  documentation
documentation:
	@echo generating documentation...
	@root -b -q scripts/make_documentation.cc >& /dev/null
#	root -b -q scripts/make_documentation.cc
	@echo done.

#rules for cleaning up
.PHONY: clean distclean
clean:
	@echo cleaning up...
	@rm -f $(OBJDIR)/*.$(ObjSuf) $(BINDIR)/*
	@rm -f $(LIBDIR)/*
	$(foreach SECT,$(DICTSECTIONS), \
	@rm -f $(SRCDIR)/$(SECT)/$(LINKDEF)/*Dict*)

distclean: clean
	@echo deleting temporary folders...
	@rm -rf $(OBJDIR)
	@rm -rf $(LIBDIR)
	@rm -rf $(BINDIR)
	@rm -rf $(HTMLDIR)
	@echo ...done.
