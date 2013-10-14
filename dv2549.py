import os
import sys
import getopt
import subprocess

def run( cmd ):
	p = subprocess.Popen(
		cmd, 
		shell=True, # ?
		stdout=subprocess.PIPE,
		stderr=subprocess.STDOUT)
	return p.communicate()

pathHere = sys.path[ 0 ]

experimentArgAcceleration = "HARD"
experimentArgPrecision	= "INT"
experimentArgs = " " + experimentArgAcceleration + " " + experimentArgPrecision
experimentPath = pathHere + "/experiment.exe";
experimentCommand = experimentPath + experimentArgs;

res = run( experimentCommand )
print( res )

# Generate matrix
#matrixgenArgPrecison = "INT"
#matrixgenArgDimension = "200"
#matrixgenArgMin = "0"
#matrixgenArgMax = "10"
#matrixgenArgs = " " + matrixgenArgPrecison + " " + matrixgenArgDimension + " " + matrixgenArgMin + " " + matrixgenArgMax
#matrixgenPath = pathHere + "\\..\\..\\matrixgen\\Release\\matrixgen.exe"
#matrixgenCommand = matrixgenPath + matrixgenArgs

# Parse arguments using getopt:
# try:
# 	opts, args = getopt.getopt( sys.argv[1:], ":n:|:h:d:|:c2rFtf" )
# except getopt.GetoptError as e:
# 	print( e )
# 	sys.exit( 2 )
	
# Interpret arguments parsed to script:
#for opt, arg in opts:
#if opt == "-n":
#printLimit = int( arg )
#if opt in ( "-h", "-d" ):
#if opt == "-h": # Now - Hours
#date = date + datetime.timedelta( hours = -int(arg) )
#elif opt == "-d": # Now - Days
#date = date + datetime.timedelta( days = -int(arg) )
#if opt in ( "-c", "-2", "-r", "-F", "-t", "-f" ):
#if opt == "-c":
#q = Queries.Queries_c
#elif opt == "-2":
#q = Queries.Queries_2
#elif opt == "-r":
#q = Queries.Queries_r
#elif opt == "-F":
#q = Queries.Queries_F
#elif opt == "-t":
#q = Queries.Queries_t
#elif opt == "-f":
#q = Queries.Queries_f