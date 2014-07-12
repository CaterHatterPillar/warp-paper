# http://bit.ly/18px6NF

import os
import sys
import getopt
import subprocess

# Relative paths
PATH_TO_EXPERIMENT	= "experiment.exe"
PATH_TO_MATRIXGEN	= "../../matrixgen/Release/matrixgen.exe"
PATH_TO_ANALYTICS	= "../../analytics/Release/analytics.exe"
PATH_TO_RESEXP		= "../../../res/" + "resExperiment.res"
PATH_TO_RESANA		= "../../../res/" + "resAnalytics.res"
PATH_TO_EXPRES		= "../../../res/"
def GetPath( rel ): # Relative to absolute path.
	return os.path.abspath( rel )

# Classes
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
class DescMat:
	def __init__( self ):
		self.prec 	= ""
		self.dim 	= ""
		self.min 	= ""
		self.max 	= ""
class DescExp:
	def __init__( self ):
		self.num 	= 0
		self.acc 	= ""
		self.prec 	= ""
		self.kernel = ""

# Factory methods
def factoryDescMat( prec, dim, min, max ):
	desc = DescMat()
	desc.prec 	= prec
	desc.dim 	= dim
	desc.min 	= min
	desc.max 	= max
	return desc
def factoryDescExp( kernel, acc, prec, num ):
	desc = DescExp()
	desc.num 	= num
	desc.acc 	= acc
	desc.prec 	= prec
	desc.kernel	= kernel
	return desc

# IO
def readResExperiment():
	res = open( GetPath( PATH_TO_RESEXP ) )
	lines = [ line.strip() for line in res ]
	linesf = []
	for line in lines:
		lineSplit = line.split( "\t", 2 )
		linesf.append( lineSplit[ 1 ] )
	re = ResExperiment()
	
	re.precision 	= int( linesf[ 2 ] )
	re.rows			= int( linesf[ 3 ] )
	re.cols			= int( linesf[ 4 ] )
	re.equal 		= bool( linesf[ 0 ] )
	re.timeMs 		= float( linesf[ 1 ] )
	res.close()
	return re
def readResAnalytics():
	res = open( GetPath( PATH_TO_RESANA ) )
	lines = [ line.strip() for line in res ]
	linesf = []
	for line in lines:
		lineSplit = line.split( "\t", 2 )
		linesf.append( lineSplit[ 1 ] )
	re = ResAnalytics()
	re.devMax = float( linesf[ 0 ] )
	re.devMin = float( linesf[ 1 ] )
	re.devStd = float( linesf[ 2 ] )
	res.close()
	return re
def writeExpRes( filename, res ):
	out = open( GetPath( filename ), "w" )
	for entry in res:
		out.write( entry + "\n" )
	out.close()

# Subprocesses
def run( cmd ):
	print( cmd + "..." )
	p = subprocess.Popen( cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT )
	return p.communicate()
def matrixgen( desc ):
	generateNewMatrices = "0";
	print( "\nGenerating matrices with properties:\n\tPrecision:\t" + desc.prec + "\n\tDimension:\t" + desc.dim + "\n\tMax:\t\t" + desc.max + "\n\tMin:\t\t" + desc.min + " " + generateNewMatrices + "\n" )
	run( GetPath( PATH_TO_MATRIXGEN ) + " " + desc.prec + " " + desc.dim + " " + desc.min + " " + desc.max + " 1" )
def experiment( desc ):
	expResMss = []
	expResDMin = []
	expResDMax = []
	expResDStd = []
	for i in range( 0, desc.num ):
		run( GetPath( PATH_TO_EXPERIMENT ) + " " + desc.kernel + " " + desc.acc + " " + desc.prec )
		run( GetPath( PATH_TO_ANALYTICS ) )
		# Collect data surrounding execution:
		resExperiment 	= readResExperiment()
		resAnalytics 	= readResAnalytics()
		expResMss.append( 	str( resExperiment.timeMs	) )
		expResDMin.append( 	str( resAnalytics.devMin 	) )
		expResDMax.append( 	str( resAnalytics.devMax 	) )
		expResDStd.append( 	str( resAnalytics.devStd 	) )
	# Save data stored during experiment:
	writeExpRes( PATH_TO_EXPRES + desc.kernel + desc.acc + desc.prec + ".mss", expResMss )
	writeExpRes( PATH_TO_EXPRES + desc.kernel + desc.acc + desc.prec + ".dmin", expResDMin )
	writeExpRes( PATH_TO_EXPRES + desc.kernel + desc.acc + desc.prec + ".dmax", expResDMax )
	writeExpRes( PATH_TO_EXPRES + desc.kernel + desc.acc + desc.prec + ".dstd", expResDStd )

# Entry point:
print( "---\ndv2549\n---" )

# Generate a viable integer matrix:
#matrixgen( factoryDescMat( "INT", "200", "0", "10" ) )

tasksI = []
#tasksI.append( factoryDescExp( "BASIC", "HARD", "INT", 100 ) )
#tasksI.append( factoryDescExp( "BASIC", "SOFT", "INT", 100 ) )
#tasksI.append( factoryDescExp( "BASIC", "WARP", "INT", 100 ) )
#tasksI.append( factoryDescExp( "TILE", "HARD", "INT", 100 ) )
#tasksI.append( factoryDescExp( "TILE", "SOFT", "INT", 100 ) )
#tasksI.append( factoryDescExp( "TILE", "WARP", "INT", 100 ) )
for task in tasksI:
	print( "\nPerforming " + str( task.num ) + " experiments with properties:\n\tAcceleration:\t" + task.acc + "\n\tPrecision:\t" + task.prec + "\n" )
	experiment( task )

# Generate a viable floating point matrix:
matrixgen( factoryDescMat( "FLOAT", "200", "0", "10" ) )

# Perform experiments of all configurations for floating point precision.
tasksF = []
tasksF.append( factoryDescExp( "BASIC", "HARD", "FLOAT", 100 ) )
tasksF.append( factoryDescExp( "BASIC", "SOFT", "FLOAT", 100 ) )
tasksF.append( factoryDescExp( "BASIC", "WARP", "FLOAT", 100 ) )
tasksF.append( factoryDescExp( "TILE", "HARD", "FLOAT", 100 ) )
tasksF.append( factoryDescExp( "TILE", "SOFT", "FLOAT", 100 ) )
tasksF.append( factoryDescExp( "TILE", "WARP", "FLOAT", 100 ) )

for task in tasksF:
	print( "\nPerforming " + str( task.num ) + " experiments with properties:\n\tAcceleration:\t" + task.acc + "\n\tPrecision:\t" + task.prec + "\n" )
	experiment( task )

print( "Finished execution." )

# These methods are not used.
def avg( list ):
	num = 0
	sum = 0
	for entry in list:
		num += 1
		sum += entry
	return sum / num

# Add command line arguments at some point in the future. A bit something like this:
# Parse arguments using getopt:
# try:
# 	opts, args = getopt.getopt( sys.argv[1:], ":h:|:s:|:w:|:if" )
# except getopt.GetoptError as e:
# 	print( e )
# 	sys.exit( 2 )

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