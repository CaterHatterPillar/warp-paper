import os
import sys
import getopt
import subprocess

def run( cmd ):
	print( "\nRunning " + cmd + "..." )
	p = subprocess.Popen(
		cmd, 
		shell=True, # ?
		stdout=subprocess.PIPE,
		stderr=subprocess.STDOUT)
	return p.communicate()

def loadRes():
	res = open( os.path.abspath( "../../../res/res.res" ) );
	lines = [ line.strip() for line in res ]
	res.close()
	return lines[ 1 ] # http://bit.ly/18px6NF

def experiment( acc, prec, times ):
	print( "\nRunning default kernel " + str(times) + " times with properties:\n\tAcceleration: " + acc + "\n\tPrecision: " + prec )
	experimentPath = os.path.abspath( "experiment.exe" )
	experimentArgs = " " + acc + " " + prec
	results = []
	for i in range( 0, times ):
		run( experimentPath + experimentArgs )
		results.append( float( loadRes() ) )
	return results
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
	out = open( os.path.abspath( "experiment.res" ), "w" )
	writeList( out, hard )
	writeList( out, soft )
	writeList( out, warp ) 
	out.close()

print( "---\ndv2549\n---" )

# Generate a viable matrix:
matrixgenArgPrecison 	= "INT"
matrixgenArgDimension 	= "200"
matrixgenArgMin 		= "0"
matrixgenArgMax 		= "10"
matrixgenArgs 			= " " + matrixgenArgPrecison + " " + matrixgenArgDimension + " " + matrixgenArgMin + " " + matrixgenArgMax
matrixgenPath 			= os.path.abspath( "../../matrixgen/Release/matrixgen.exe" )
matrixgenCommand 		= matrixgenPath + matrixgenArgs
print( "\nGenerating matrices with properties:\n\tPrecision: " + matrixgenArgPrecison + "\n\tDimension: " + matrixgenArgDimension + "\n\tMax: " + matrixgenArgMax + "\n\tMin: " + matrixgenArgMin )
run( matrixgenCommand )

# Execute tests:
experimentArgPrecision = "INT"
resultsHard = experiment( "HARD", experimentArgPrecision, 100 )
resultsSoft = experiment( "SOFT", experimentArgPrecision, 100 )
resultsWarp = experiment( "WARP", experimentArgPrecision, 100 )
write( resultsHard, resultsSoft, resultsWarp )

input( "Finished execution." )

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