find_package(Doxygen REQUIRED)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(DoxygenUtilities)

# ------------------------
# Doxygen targets
# ------------------------
add_doxygen_target(
    statefox
    "StateFox"
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_BINARY_DIR}/docs/statefox"
)

# ------------------------
# Copy CSS for landing page
# ------------------------
add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/docs/style.css
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/style.css
            ${CMAKE_BINARY_DIR}/docs/style.css
)
add_custom_target(copy_docs_assets ALL
    DEPENDS ${CMAKE_BINARY_DIR}/docs/style.css
)

# ------------------------
# Bridge page
# ------------------------
set(PROJECT_NAME "StateFox")
set(PROJECT_DESC "C library for lightweight, event-driven state machines.")
set(GITHUB_REPO_URL "https://github.com/jackcenter/statefox")

# Bridge page HTML content
set(DOC_MODULES "")
set(DOC_MODULES "${DOC_MODULES}<div class=\"card\"><a href=\"statefox/html/index.html\">StateFox Library</a></div>")

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/index.html.in
    ${CMAKE_BINARY_DIR}/docs/index.html
    @ONLY
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/style.css
    ${CMAKE_BINARY_DIR}/docs/style.css
    COPYONLY
)

add_custom_target(docs ALL
    DEPENDS statefox_doc 
    COMMENT "Generating documentation landing page"
)
