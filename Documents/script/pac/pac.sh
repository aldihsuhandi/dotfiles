# !/bin/sh
operation=$1
# echo $operation
# if [ -f $operation ] ; then
#     case $operation in
#         install)  echo "install" ;;
#     esac
# else
#     echo "Unkown command"
# fi
if [ -z $operation ]
then
    echo "Unknown command"
elif [ $operation = "help" ]
then
    cat $HOME/Documents/script/pac/help
elif [ $operation = "install" ]
then
    packages=""
    for ((i = 2;i <= $#;i++)); do
        packages+=${!i}
        packages+=" "
    done
    yay -S $packages
elif [ $operation = "uninstall" ]
then
    packages=""
    for ((i = 2;i <= $#;i++)); do
        packages+=${!i}
        packages+=" "
    done
    yay -R $packages
elif [ $operation = "update" ]
then
    yay
elif [ $operation = "search" ]
then
    flag2=$2
    if [ -z $flag2 ]
    then
        echo "incomplete command"
    elif [ $flag2 = "installed" ]
    then
        pacman -Qs $3
    else
        yay -Ss $2
    fi
elif [ $operation = "clear" ]
then
    flag2=$2
    if [ -z $flag2 ]
    then
        echo "Unknown command"
    elif [ $flag2 = "cache" ]
    then
        sudo pacman -Scc
    elif [ $flag2 = "orphans" ]
    then
        sudo pacman -Rsn $(pacman -Qdtq)
    else
        echo "Unknown command"
    fi
elif [ $operation = "refresh" ]
then
    sudo pacman -Syyy
else
    echo "Unknown command"
fi

