import os
import sys
import getopt
import subprocess

# Relative paths
def GetPath( rel ): # Relative to absolute path.
        return os.path.abspath( rel )

def avg( list ):
        num = 0
        sum = 0
        for entry in list:
                num += 1
                sum += entry
        return sum / num
def read( filename ):
        res = open( GetPath( filename ) )
        lines = [ float( line.strip() ) for line in res ]
        return lines
def write( filename, avg ):
        out = open( GetPath( filename + ".avg" ), "w" )
        out.write( str( avg ) )
        out.close()
def readAvgWrite( filename ):
        write( filename, avg( read( filename ) ) )

# Entry point:
print( "---\ndv2549_avg\n---" )

# BASIC
readAvgWrite( "BASIC" + "HARD" + "FLOAT" + ".dmax" )
readAvgWrite( "BASIC" + "HARD" + "FLOAT" + ".dmin" )
readAvgWrite( "BASIC" + "HARD" + "FLOAT" + ".dstd" )
readAvgWrite( "BASIC" + "HARD" + "FLOAT" + ".mss" )

readAvgWrite( "BASIC" + "HARD" + "INT" + ".dmax" )
readAvgWrite( "BASIC" + "HARD" + "INT" + ".dmin" )
readAvgWrite( "BASIC" + "HARD" + "INT" + ".dstd" )
readAvgWrite( "BASIC" + "HARD" + "INT" + ".mss" )

readAvgWrite( "BASIC" + "SOFT" + "FLOAT" + ".dmax" )
readAvgWrite( "BASIC" + "SOFT" + "FLOAT" + ".dmin" )
readAvgWrite( "BASIC" + "SOFT" + "FLOAT" + ".dstd" )
readAvgWrite( "BASIC" + "SOFT" + "FLOAT" + ".mss" )

readAvgWrite( "BASIC" + "SOFT" + "INT" + ".dmax" )
readAvgWrite( "BASIC" + "SOFT" + "INT" + ".dmin" )
readAvgWrite( "BASIC" + "SOFT" + "INT" + ".dstd" )
readAvgWrite( "BASIC" + "SOFT" + "INT" + ".mss" )

readAvgWrite( "BASIC" + "WARP" + "FLOAT" + ".dmax" )
readAvgWrite( "BASIC" + "WARP" + "FLOAT" + ".dmin" )
readAvgWrite( "BASIC" + "WARP" + "FLOAT" + ".dstd" )
readAvgWrite( "BASIC" + "WARP" + "FLOAT" + ".mss" )

readAvgWrite( "BASIC" + "WARP" + "INT" + ".dmax" )
readAvgWrite( "BASIC" + "WARP" + "INT" + ".dmin" )
readAvgWrite( "BASIC" + "WARP" + "INT" + ".dstd" )
readAvgWrite( "BASIC" + "WARP" + "INT" + ".mss" )

# TILE
readAvgWrite( "TILE" + "HARD" + "FLOAT" + ".dmax" )
readAvgWrite( "TILE" + "HARD" + "FLOAT" + ".dmin" )
readAvgWrite( "TILE" + "HARD" + "FLOAT" + ".dstd" )
readAvgWrite( "TILE" + "HARD" + "FLOAT" + ".mss" )

readAvgWrite( "TILE" + "HARD" + "INT" + ".dmax" )
readAvgWrite( "TILE" + "HARD" + "INT" + ".dmin" )
readAvgWrite( "TILE" + "HARD" + "INT" + ".dstd" )
readAvgWrite( "TILE" + "HARD" + "INT" + ".mss" )

readAvgWrite( "TILE" + "SOFT" + "FLOAT" + ".dmax" )
readAvgWrite( "TILE" + "SOFT" + "FLOAT" + ".dmin" )
readAvgWrite( "TILE" + "SOFT" + "FLOAT" + ".dstd" )
readAvgWrite( "TILE" + "SOFT" + "FLOAT" + ".mss" )

readAvgWrite( "TILE" + "SOFT" + "INT" + ".dmax" )
readAvgWrite( "TILE" + "SOFT" + "INT" + ".dmin" )
readAvgWrite( "TILE" + "SOFT" + "INT" + ".dstd" )
readAvgWrite( "TILE" + "SOFT" + "INT" + ".mss" )

readAvgWrite( "TILE" + "WARP" + "FLOAT" + ".dmax" )
readAvgWrite( "TILE" + "WARP" + "FLOAT" + ".dmin" )
readAvgWrite( "TILE" + "WARP" + "FLOAT" + ".dstd" )
readAvgWrite( "TILE" + "WARP" + "FLOAT" + ".mss" )

readAvgWrite( "TILE" + "WARP" + "INT" + ".dmax" )
readAvgWrite( "TILE" + "WARP" + "INT" + ".dmin" )
readAvgWrite( "TILE" + "WARP" + "INT" + ".dstd" )
readAvgWrite( "TILE" + "WARP" + "INT" + ".mss" )