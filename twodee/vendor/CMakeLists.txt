# Import vendored libraries
include_directories(glm)

# Copy dirs from property into separate variable. We do this rather than simply
# listing the directories in a variable definition because the paths retrieved
# from the property will be converted to absolute paths.
get_property(VENDOR_INCLUDE_DIRECTORIES DIRECTORY PROPERTY INCLUDE_DIRECTORIES)

# expose variable to parent scope to allow use by sublings
set(VENDOR_INCLUDE_DIRECTORIES ${VENDOR_INCLUDE_DIRECTORIES} PARENT_SCOPE)
