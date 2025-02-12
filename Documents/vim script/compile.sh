filename=$(echo $1 | cut -f1 -d".")
if [ -f $1 ] ; then
    case $1 in
        *.cpp)      g++ -o $filename $1 -std=gnu++17 -Wall -Wextra -Wshadow;;
        *.c)        gcc -o $filename $1 -std=c11 -Wall -Wextra -lm -Wshadow;;
        *.java)     javac $1;;
        *.py)       python $1;;
        *)          echo "'$1' cannot be compile via compile()" ;;
    esac
else
    echo "'$1' is not a valid file"
fi

