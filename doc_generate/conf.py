import os
import sys
import subprocess
import datetime
import glob
import re

from typing import Any, Dict, List

def multi_glob(*glob_patterns: str) -> List[str]:
    """Expand the glob_patterns to a list of matching files/directories.

    :return: A list of matching files/directories.
    :rtype: List[str]
    """
    result = []
    for p in glob_patterns:
        for path in glob.glob(p):
            result.append(path)
    return result

sys.path.append(os.path.abspath("."))

# General information about the project.
project             = "Splines"
html_show_copyright = False

# The version info for the project you're documenting, acts as replacement for
# |version| and |release|, also used in various other places throughout the
# built documents.
# version = informational_version_from_ci('0.1.0-local-development-version')
# release = semantic_version_from_ci('0.1')
version = f"{subprocess.check_output(["git", "describe", "--abbrev=0"]).decode("utf-8")}"
release = "2.0"

# -- General configuration ---------------------------------------------------
needs_sphinx   = "4.4.0"
source_suffix = {
    '.rst': 'restructuredtext',
    '.md':  'markdown',
    '.txt': 'markdown',
}
master_doc     = "index"
language       = "en"
templates_path = ["_templates"]

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path .
exclude_patterns = multi_glob(
  ".*",
  "_*",
  "build",
  "README-DOC.md",
  "doxygen-doc-env.yml"
)

# -- Options for HTML output -------------------------------------------------
# Configure HTML theme (remember to also change doxysphinx)
#html_theme = "sphinx_nefertiti" # NON MALE
html_theme = 'agogo' # BELLO
#html_theme = "sphinx_rtd_theme"

html_static_path   = ["_static/"]
html_title         = project
html_css_files     = ["custom.css"]
html_logo          = "Figlet.png"

html_theme_options = {
  "bodyfont"        : "-apple-system, 'BlinkMacSystemFont', 'Segoe UI', Roboto, Oxygen, Ubuntu, Cantarell, 'Fira Sans', 'Droid Sans', 'Helvetica Neue', sans-serif;",
  "headerfont"      : "Verdana,'DejaVu Sans',Geneva,sans-serif;",
  "pagewidth"       : "70em",
  "documentwidth"   : "52em",
  "rightsidebar"    : "true",
  "sidebarwidth"    : "18em",
  "bgcolor"         : "#eeeeec",
  "headerbg"        : "#555573 url(bgtop.png) top left repeat-x",
  "footerbg"        : "url(bgfooter.png) top left repeat-x",
  "linkcolor"       : "#ce5c00",
  "headercolor1"    : "#204a87",
  "headercolor2"    : "#3465a4",
  "headerlinkcolor" : "#fcaf3e",
  "textalign"       : "justify",
}

#    --font-family: -apple-system, BlinkMacSystemFont, Segoe UI, Roboto, Oxygen, Ubuntu, Cantarell, Fira Sans, Droid Sans, Helvetica Neue, sans-serif;
#    --font-family-monospace: ui-monospace, SFMono-Regular, SF Mono, Menlo, Consolas, Liberation Mono, monospace;



# -- Sphinx extensions -------------------------------------------------------
extensions = [
    "sphinx_needs",
    #"sphinxcontrib.plantuml",
    "sphinx.ext.mathjax",
    "sphinx.ext.ifconfig",
    "sphinx.ext.autodoc",
    "sphinx.ext.viewcode",
    "matplotlib.sphinxext.plot_directive",
    "sphinx.ext.duration",
    "sphinx.ext.napoleon",
    "sphinx.ext.graphviz",
    "sphinx.ext.todo",
    "sphinx_copybutton",
    "myst_parser",
    #"sphinx_mdinclude",
    #"sphinxcontrib.doxylink",
    "sphinx.ext.inheritance_diagram",
    "sphinx_design"
]

# Myst
myst_enable_extensions = [
    "amsmath",
    "attrs_inline",
    "colon_fence",
    "deflist",
    "dollarmath",
    "fieldlist",
    "html_admonition",
    "html_image",
    #"linkify",
    #"replacements",
    "smartquotes",
    "strikethrough",
    #"substitution",
    "tasklist",
]
myst_heading_anchors = 4

# needs
# types definition for sphinx needs
needs_types = [
    {
        "directive": "component",
        "title": "Software Component",
        "prefix": "COMP_",
        "color": "#99E8FF",
        "style": "component",
    },
    {
        "directive": "feature",
        "title": "Software Feature",
        "prefix": "FEAT_",
        "color": "#58DD63",
        "style": "folder",
    },
    {
        "directive": "req",
        "title": "Software Requirement",
        "prefix": "REQ_",
        "color": "#37CCB8",
        "style": "folder",
    },
    {
        "directive": "test",
        "title": "Software Test",
        "prefix": "TEST_",
        "color": "#DDA01A",
        "style": "folder",
    },
]

needs_extra_options = ["category", "provider"]

needs_extra_links = [
    {"option": "requires", "incoming": "is required by", "outgoing": "requires"},
    {
        "option": "derives",
        "incoming": "is derived to",
        "outgoing": "is derived from",
    },
    {
        "option": "implements",
        "incoming": "is implemented by",
        "outgoing": "implements",
    },
    {"option": "tracks", "incoming": "tracks", "outgoing": "is tracked by"},
]
