TARGET = libcocosext.a

COCOS_ROOT=../..

INCLUDES = -I$(COCOS_ROOT)/external \
	-I$(COCOS_ROOT)/CocosDenshion/include \
	-I.. \
	-I../GUI \
	-I../misc \

SOURCES = ../misc/CocosUtils.cpp \
../GUI/Layout.cpp \
../GUI/LinearLayout.cpp \
../GUI/MenuItemFactory.cpp \

include $(COCOS_ROOT)/cocos2dx/proj.linux/cocos2dx.mk

CXXFLAGS += -Wno-multichar -Wno-delete-non-virtual-dtor

TARGET := $(LIB_DIR)/$(TARGET)

all: $(TARGET)

$(TARGET): $(OBJECTS) $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_AR)$(AR) $(ARFLAGS) $@ $(OBJECTS)

$(OBJ_DIR)/%.o: ../%.cpp $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CXX)$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@

$(OBJ_DIR)/%.o: ../%.c $(CORE_MAKEFILE_LIST)
	@mkdir -p $(@D)
	$(LOG_CC)$(CC) $(CCFLAGS) $(INCLUDES) $(DEFINES) -c $< -o $@
