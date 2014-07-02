#!/bin/python

import os
import sys
import subprocess

os.chdir('tex/eurosis')

subprocess.call("pdflatex -shell-escape eurosis.tex", shell=True)

subprocess.call(["bibtex", "web.aux"])
subprocess.call(["bibtex", "eurosis.aux"])

subprocess.call("pdflatex -shell-escape eurosis.tex", shell=True)
subprocess.call("pdflatex -shell-escape eurosis.tex", shell=True)
