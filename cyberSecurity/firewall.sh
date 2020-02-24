# !/bin/bash/

while [[ true ]]; do

    echo "
    -=-=-=-=-= FIREWALL EDITOR =-=-=-=-=-
    1 - Add rule
    2 - Modify rule
    3 - Delete rule
    4 - Output Report
    0 - Quit
    h - Help
    "
    echo -n "Enter Option: "
    read option

    if [[ $option == "1" ]]; then
        
        echo "

        -=-=-= Add Rule =-=-=-
        INPUT
        FORWARD
        OUTPUT
        help
        "
        echo -n "Enter chain: "
        read chain

        if [[ $chain == "help" ]]; then
            echo "

            -= Help =-
            1 - INPUT - This chain is used to control the behavior for incoming connections. 
            2 - FORWARD - This chain is used for incoming connections that aren’t actually being delivered locally.
            3 - OUTPUT - This chain is used for outgoing connections.
            "
            echo -n "Enter chain: "
            read chain

        fi

        echo -n "

        -=-=-= Add Rule =-=-=-
        Enter IP Address:"
        read ipaddress
       
        echo "
        
        -=-=-= Add Rule =-=-=-
        ACCEPT
        DROP
        "
        echo -n "Enter what you want to do with  the connection: "
        read preference

        echo -n "
        
        $preference connections from $chain $ipaddress? [y/n]:
        "
        read confirmation
        if [[ ${confirmation^} == "Y" ]]; then
            iptables -A ${chain^^} -s ${ipaddress^^} -j ${preference^^}
            echo "Done . . . "
        fi


    elif [[ $option == "2" ]]; then

        echo "

        -=-=-= Modify Rule =-=-=-
        "
    elif [[ $option == "3" ]]; then

        echo "

        -=-=-= Delete Rule =-=-=-
        INPUT
        FORWARD
        OUTPUT
        help        
        "

        echo -n "Enter chain containing rule to delete: "
        read chain

        if [[ $chain == "help" ]]; then
            echo "

            -= Help =-
            1 - INPUT - This chain is used to control the behavior for incoming connections. 
            2 - FORWARD - This chain is used for incoming connections that aren’t actually being delivered locally.
            3 - OUTPUT - This chain is used for outgoing connections.
            "
            echo -n "Enter chain: "
            read chain
        fi

        iptables -L ${chain^^} --line-numbers

        echo -n "Enter rule number to delete: "
        read rule

        echo -n "
        
        Delete rule $rule from $chain? [y/n]:
        "
        read confirmation
        if [[ ${confirmation^} == "Y" ]]; then
            iptables -D ${chain^^} $rule
            echo "Done . . . "
        fi


    elif [[ $option == "4" ]]; then

        echo "

        Report outputted
        "

    elif [[ $option == "0" ]]; then
        echo "
        Goodbye . . . 
        "
        exit 0

    elif [[ $option == "h" ]]; then

        echo "

        -=-=-= Help =-=-=-
        "

    else
        echo "Command not recognized . . . "
    fi
    
    read -p "Enter to continue . . . "
done