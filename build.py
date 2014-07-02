#!/bin/python

import os
import sys
import subprocess

os.chdir('tex/gameon')

subprocess.call("pdflatex -shell-escape GAME_HARD_01.tex", shell=True)

subprocess.call(["bibtex", "web.aux"])
subprocess.call(["bibtex", "GAME_HARD_01.aux"])

subprocess.call("pdflatex -shell-escape GAME_HARD_01.tex", shell=True)
subprocess.call("pdflatex -shell-escape GAME_HARD_01.tex", shell=True)
