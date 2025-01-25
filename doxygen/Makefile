DOXYFILE = doxyfile_utils

.PHONY: help clean html doxygen doxysphinx sphinx

clean:
	@rm -rf docs*

html:
	@doxygen $(DOXYFILE)

install:
	@rm -rf ../docs*
	@mkdir  ../docs
	@touch  ../docs/.nojekyll
	@cp -rf docs/html/. ../docs
