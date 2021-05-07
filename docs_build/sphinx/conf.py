# -*- coding: utf-8 -*-
import os
from pathlib import Path

# -- Project information -----------------------------------------------------
exec(open("../project_common.py").read())


rst_prolog = ".. |xml| replace:: %s\n" % (project)

extensions.append('breathe');
extensions.append('exhale');

breathe_projects = {
}

breathe_default_project = "doc_cpp"

dir_path_cpp = os.path.dirname(os.path.realpath(__file__))+"../../../src"
dir_path_cpp = Path(dir_path_cpp).resolve()

doxygen_common_stdin = """
        EXTRACT_ALL         = YES
        SOURCE_BROWSER      = YES
        EXTRACT_STATIC      = YES
        HIDE_SCOPE_NAMES    = NO
        CALLER_GRAPH        = YES
        GRAPHICAL_HIERARCHY = YES
        HAVE_DOT            = YES
        QUIET               = NO
        GENERATE_TREEVIEW   = YES
        SHORT_NAMES         = YES
        IMAGE_PATH          = ../images

        XML_PROGRAMLISTING    = YES
        RECURSIVE             = YES
        FULL_PATH_NAMES       = YES
        ENABLE_PREPROCESSING  = YES
        MACRO_EXPANSION       = YES
        SKIP_FUNCTION_MACROS  = NO
        EXPAND_ONLY_PREDEF    = NO
        INHERIT_DOCS          = YES
        INLINE_INHERITED_MEMB = YES
        EXTRACT_PRIVATE       = YES
        PREDEFINED           += protected=private
        GENERATE_HTML         = NO
"""

exhale_projects_args = {
}

#cpp_index_common_prefix = ['calc_defs::']
#html_extra_path  = [ 'extra_files' ]