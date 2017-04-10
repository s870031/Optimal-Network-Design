#
# This script rearranges the graph in dot file
#	into circle arrangment and transfer the dot 
#   file into png file.

# Check if file exist
if [ ! -f $1 ]; then
	echo "$1 File not Found"

# Check if it's a dot file
elif [[ ! $1 =~ \.dot$ ]]; then
	echo "$1 is not a Dot File"

# Rearrange and transfer the file
else
	circledotfile=$(echo $1 | sed 's/\.dot/_circle\.dot/')
	circo $1 > $circledotfile
	neato -n $circledotfile -Tpng -O
fi
