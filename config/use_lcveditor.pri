# The configuration for projects depending on the lcveditor



LCVEDITOR_INCLUDE_DIR = $$PATH_SOURCE_EDITOR_LCVEDITOR/src

!exists($$LCVEDITOR_INCLUDE_DIR): \
    error($$_FILE_: Could not find $$LCVEDITOR_INCLUDE_DIR)

LIBS += -L$$PATH_DEPLOY_APPLICATION -llcveditor
INCLUDEPATH += $$LCVEDITOR_INCLUDE_DIR
DEPENDPATH  += $$LCVEDITOR_INCLUDE_DIR
