# http://bit.ly/18px6NF

import os
import sys
import getopt
import subprocess

class ResExperiment:
	def __init__( self ):
		self.equal 		= True
		self.timeMs 	= 0.0
		self.precision 	= 0
		self.rows		= 0
		self.cols		= 0
class ResAnalytics:
	def __init__( self ):
		self.devMax = 0.0
		self.devMin = 0.0
		self.devStd = 0.0

def readResExperiment():
	res = open( os.path.abspath( "../../resExperiment.res" ) )
	lines = [ line.strip() for line in res ]
	linesf = []
	for line in lines:
		lineSplit = line.split( "\t", 2 )
		linesf.append( lineSplit[ 1 ] )
	re = ResExperiment()
	re.equal 		= bool( linesf[ 0 ] )
	re.timeMs 		= float( linesf[ 1 ] )
	re.precision 	= int( linesf[ 2 ] )
	re.rows			= int( linesf[ 3 ] )
	re.cols			= int( linesf[ 4 ] )
	return re

def readResAnalytics():
	res = open( os.path.abspath( "../../resAnalytics.res" ) )
	lines = [ line.strip() for line in res ]
	linesf = []
	for line in lines:
		lineSplit = line.split( "\t", 2 )
		linesf.append( lineSplit[ 1 ] )
	re = ResAnalytics()
	re.devMax = float( linesf[ 0 ] )
	re.devMin = float( linesf[ 1 ] )
	re.devStd = float( linesf[ 2 ] )
	return re

def writeRes( resExperiment, resAnalytics ):
	print( resExperiment.timeMs )

def run( cmd ):
	print( "\nRunning " + cmd + "..." )
	p = subprocess.Popen(
		cmd, 
		shell=True, # ?
		stdout=subprocess.PIPE,
		stderr=subprocess.STDOUT)
	return p.communicate()

def experiment( acc, prec, times ):
	#print( "\nRunning default kernel " + str(times) + " times with properties:\n\tAcceleration: " + acc + "\n\tPrecision: " + prec )
	experimentPath = os.path.abspath( "experiment.exe" )
	experimentArgs = " TILE " + acc + " " + prec
	results = []
	for i in range( 0, times ):
		run( experimentPath + experimentArgs )
		resExperiment = readResExperiment()
		resAnalytics = readResAnalytics()
		writeRes( resExperiment, resAnalytics )
	return results

# These methods are not used.
def avg( list ):
	num = 0
	sum = 0
	for entry in list:
		num += 1
		sum += entry
	return sum / num
def writeList( file, list ):
	file.write( str( avg( list ) ) + "\n" )
	file.write( str( min( list ) ) + "\n" )
	file.write( str( max( list ) ) + "\n" )
	for entry in list:
		file.write( str( entry ) + "\n" )
	file.write( "\n" )
def write( hard, soft, warp ):
	out = open( os.path.abspath( "../../../dv2549.res" ), "w" )
	writeList( out, hard )
	writeList( out, soft )
	writeList( out, warp ) 
	out.close()

print( "---\ndv2549\n---" )
# Parse arguments using getopt:
# try:
# 	opts, args = getopt.getopt( sys.argv[1:], ":h:|:s:|:w:|:if" )
# except getopt.GetoptError as e:
# 	print( e )
# 	sys.exit( 2 )

# tasks		= []
# taskArgs 	= []
# precision 	= "INT"
# # Interpret arguments parsed to script:
# for opt, arg in opts:
# 	if opt in ( "-h", "-s", "-w" ): # Task
# 		if opt=="-h": # Hardware
# 			tasks.append( "HARD" )
# 		elif opt=="-s": # Software
# 			tasks.append( "SOFT" )
# 		elif opt=="-w": # WARP
# 			tasks.append( "WARP" )
# 		taskArgs.append( int( arg ) )
# 	if opt in ( "-i", "-f" ): # Precision
# 		if opt == "-i": # Integer
# 			precision = "INT"
# 		elif opt == "-f": # Float
# 			precision = "FLOAT"

precision = "FLOAT"

# Generate a viable matrix:
matrixgenArgPrecison 	= precision
matrixgenArgDimension 	= "200"	
matrixgenArgMin 		= "0"	# Currently default values.
matrixgenArgMax 		= "10"	
matrixgenArgs 			= " " + matrixgenArgPrecison + " " + matrixgenArgDimension + " " + matrixgenArgMin + " " + matrixgenArgMax
matrixgenPath 			= os.path.abspath( "../../Release/matrixgen.exe" )
matrixgenCommand 		= matrixgenPath + matrixgenArgs
print( "\nGenerating matrices with properties:\n\tPrecision: " + matrixgenArgPrecison + "\n\tDimension: " + matrixgenArgDimension + "\n\tMax: " + matrixgenArgMax + "\n\tMin: " + matrixgenArgMin )
run( matrixgenCommand )

# Perform experiments:
#for i, task in enumerate( tasks ):
#	experiment( task, precision, taskArgs[ i ] )

experiment( "HARD", precision, 10 )

input( "Finished execution." )